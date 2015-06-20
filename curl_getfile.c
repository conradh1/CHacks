#include <curl/curl.h>
#include <cstdio>

// link with libcurl. eg.
// // g++ -Wall -std=c++98 -pedantic -Werror -lcurl -I /usr/local/include    -L /usr/local/lib

void get_page( const char* url, const char* file_name )
{
   CURL* easyhandle = curl_easy_init() ;

   curl_easy_setopt( easyhandle, CURLOPT_URL, url ) ;

   std::FILE* <strong class="highlight">file</strong> = std::fopen( file_name, "w" ) ;
   curl_easy_setopt( easyhandle, CURLOPT_WRITEDATA, <strong class="highlight">file</strong> ) ;

  curl_easy_perform( easyhandle );

  curl_easy_cleanup( easyhandle );
}

int main()
{
  get_page( "www.research.att.com/~bs/",
            "/tmp/stroustrup_home_page.html" ) ;
}
