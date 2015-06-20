/**
 * Simple example to parse a file called "file.xml", 
 * walk down the DOM, and print the name of the 
 * xml elements nodes.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * COMPAT using xml-config --cflags to get the include path this will
 * use libxml2-2.1.0 + 
 */
#include <libxml/xmlmemory.h>
#include <libxml/parser.h> 

#include "validateJobManifest.h"

int main(int argc, char **argv)
{
    
    batch *newBatchPtr;

    newBatchPtr= parseBatches(newBatchPtr, "job_manifest.xml");
    printBatches( newBatchPtr);

    return 0;
}
