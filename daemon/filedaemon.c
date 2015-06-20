//-----------------------------------------------------------------------------
// Copyright © 2003 - Philip Howard - All rights reserved
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//-----------------------------------------------------------------------------
// package	libh/daemon
// purpose	Support daemon startup
// homepage	http://libh.slashusr.org/
//-----------------------------------------------------------------------------
// author	Philip Howard
// email	libh at ipal dot org
// homepage	http://phil.ipal.org/
//-----------------------------------------------------------------------------
// This file is best viewed using a fixed spaced font such as Courier
// and in a display at least 120 columns wide.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// program	filedaemon
//
// purpose	Output a specified file to an incoming connection to
//		a specified TCP port.
//
//		This is something semi-useful to show how to make a simple
//		server using the daemon library.
//
// syntax	filedaemon  portnumber  filename
//-----------------------------------------------------------------------------
#include <fcntl.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#include <libh/daemon.h>

//-----------------------------------------------------------------------------
// Define macros to select which madvise appears to be available.
// If none appears available, then just define them as zero.
//-----------------------------------------------------------------------------
#ifdef MADV_SEQUENTIAL
#define madvise_sequential(p,s)	madvise((p),(s),MADV_SEQUENTIAL)
#else
#ifdef POSIX_MADV_SEQUENTIAL
#define madvise_sequential(p,s)	posix_madvise((p),(s),POSIX_MADV_SEQUENTIAL)
#else
#define madvise_sequential(p,s)	(0)
#endif
#endif

#ifdef MADV_DONTNEED
#define madvise_dontneed(p,s)	madvise((p),(s),MADV_DONTNEED)
#else
#ifdef POSIX_MADV_DONTNEED
#define madvise_dontneed(p,s)	posix_madvise((p),(s),POSIX_MADV_DONTNEED)
#else
#define madvise_dontneed(p,s)	(0)
#endif
#endif

//-----------------------------------------------------------------------------
// Main program.
//-----------------------------------------------------------------------------
int
main (
    int		argc
    ,
    char * *	argv
    )
{
    static int		num1		= 1;

    struct stat		stat_buf	;
    struct sockaddr_in	sock_addr	;
    socklen_t		sock_addrlen	;
    struct servent *	servent_p	;
    char *		program_name	;
    char *		file_name	;
    long		start_count	;
    int			master_pid	;
    int			port_number	;
    int			fd		;

    int			fd_list		[2]	;


    //--------------------------------------------------------
    // At this point main() is running in the startup process.
    // This is the process that the shell is waiting to exit.
    //--------------------------------------------------------
    program_name = argv[0];
    daemon_set_program_name( program_name );

    //------------------------------------
    // Make sure we have enough arguments.
    //------------------------------------
    if ( argc <= 2 ) {
	fprintf( stderr, "%s: need arguments:  portnumber  filename\n", program_name );
	return 1;
    }

    //---------------------
    // Get the port number.
    //---------------------
    if ( '0' <= argv[1][0] && argv[1][0] <= '9' ) {
	port_number = strtoul( argv[1], NULL, 0 );
    } else {
	servent_p = getservbyname( argv[1], "tcp" );
	if ( ! servent_p ) {
	    fprintf( stderr, "%s: unrecognized service port \"%s\"\n", program_name, argv[1] );
	    return 1;
	}
	port_number = servent_p->s_port;
    }
    if ( port_number > 65535 ) {
	fprintf( stderr, "%s: invalid port number \"%u\"\n", program_name, port_number );
	return 1;
    }

    //----------------------------------------------------
    // Get the file name.  It does not have to exist, yet.
    //----------------------------------------------------
    file_name = argv[2];
    if ( stat( file_name, & stat_buf ) < 0 ) {
	fprintf( stderr, "WARNING: file \"%s\" does not exist, yet\n", file_name );
    } else {
	if ( ! S_ISREG( stat_buf.st_mode ) ) {
	    fprintf( stderr, "WARNING: file \"%s\" exists but is not a regular file\n", file_name );
	}
    }

    //----------------------------------------------
    // Run startup loop which starts master process.
    //----------------------------------------------
    daemon_set_start_timeout( 30 );
    if ( daemon_start() < 0 ) _exit( 1 );

    //-------------------------------
    // Now running in master process.
    //-------------------------------
    argv[0][0] = 'M';
    master_pid = getpid();

    //--------------------------
    // Set up the listen socket.
    //--------------------------
    sock_addrlen = sizeof ( sock_addr );
    sock_addr.sin_family = AF_INET;
    fd_list[0] = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( fd_list[0] < 0 ) {
	perror( "socket(PF_INET,SOCK_STREAM,IPPROTO_TCP)" );
	_exit( 1 );
    }
    if ( setsockopt( fd_list[0], SOL_SOCKET, SO_REUSEADDR, (void*) & num1, (socklen_t) sizeof ( num1 ) ) < 0 ) {
	perror( "setsockopt(,SOL_SOCKET,SO_REUSEADDR,,)" );
	_exit( 1 );
    }
    memset( & sock_addr, 0, sock_addrlen );
    sock_addr.sin_port = htons( (u_int16_t) port_number );
    sock_addr.sin_addr.s_addr = 0;
    if ( bind( fd_list[0], (struct sockaddr *) & sock_addr, (socklen_t) sock_addrlen ) < 0 ) {
	perror( "bind(fd_list[0],,)" );
	_exit( 1 );
    }
    if ( listen( fd_list[0], 128 ) < 0 ) {
	perror( "listen(,128)" );
	_exit( 1 );
    }
    fd_list[1] = -1;

    //------------------------------------------------------------
    // Run master loop which starts and restarts server processes.
    //------------------------------------------------------------
    daemon_set_restart_count_max( 256 );
    if ( daemon_master( & start_count ) != 0 ) {
	_exit( 1 );
    }

    //-------------------------------
    // Now running in server process.
    //-------------------------------
    argv[0][0] = 'S';

    //-----------------------------------------------------
    // If this is the first server start, output a message.
    //-----------------------------------------------------
    if ( start_count == 0 ) {
	fprintf( stderr, "master PID = %u , server PID = %u\n", master_pid, getpid() );
	daemon_success();
    }

    //---------------------------------------------------
    // Set maximum number of concurrent worker processes.
    //---------------------------------------------------
    daemon_set_worker_count_max( 40 );

    //-------------------------------------------------------------------
    // Run server loop which starts a worker process for each connection.
    //-------------------------------------------------------------------
    if ( daemon_server( fd_list, (struct sockaddr *) & sock_addr, & sock_addrlen ) < 0 ) _exit( 1 );

    //-------------------------------
    // Now running in worker process.
    //-------------------------------
    argv[0][0] = 'W';

    //---------------------------
    // Access the specified file.
    //---------------------------
    if ( stat( file_name, & stat_buf ) < 0 )		_exit( 1 );
    if ( ! S_ISREG( stat_buf.st_mode ) )		_exit( 1 );
    if ( ( fd = open( file_name, O_RDONLY ) ) < 0 )	_exit( 1 );

    //---------------------
    // Copy file to stdout.
    //---------------------
    {
	off_t map_offset;
	map_offset = 0;
	while ( map_offset < stat_buf.st_size ) {
	    void *map_ptr;
	    size_t map_size = 65536;
	    if ( map_offset + map_size > stat_buf.st_size ) map_size = stat_buf.st_size - map_offset;
	    map_ptr = mmap( 0, map_size, PROT_READ, MAP_SHARED, fd, map_offset );
	    if ( map_ptr == MAP_FAILED ) _exit( 1 );
	    madvise_sequential( map_ptr, map_size );
	    {
		void *write_ptr = map_ptr;
		size_t write_size = map_size;
		while ( write_size ) {
		    ssize_t write_len;
		    if ( ( write_len = write( 1, write_ptr, write_size ) ) < 0 ) _exit( 1 );
		    write_ptr += write_len;
		    write_size -= write_len;
		}
	    }
	    madvise_dontneed( map_ptr, map_size );
	    if ( munmap( map_ptr, map_size ) < 0 ) _exit( 1 );
	    map_offset += map_size;
	}
    }

    //----------------
    // Close and exit.
    //----------------
    shutdown( 1, SHUT_WR );
    close( fd );
    _exit( 0 );
}
