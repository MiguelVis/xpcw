/*	pcwfont.c

	Manages the Amstrad PCW internal font.

	Uses the XPCW library.

	Copyright (c) 2015 Miguel Garcia / FloppySoftware

	This program is free software; you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by the
	Free Software Foundation; either version 2, or (at your option) any
	later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

	To compile with MESCC:

	cc fontch
	ccopt fontch
	zsm fontch
	hexcom fontch
	gencom fontch.com xpcw.rsx

	Changes:

	23 Sep 2015 : v1.00 : 1st version.
	17 Nov 2016 : v1.01 : Documented a bit.	Minor modifications in usage text.
*/

/* Defs. for MESCC
   ---------------
*/
#define CC_FREAD   // To include fread()
#define CC_FWRITE  // To include fwrite()

/* Standard MESCC library
   ----------------------
*/
#include <mescc.h>

/* Standard MESCC libraries
   ------------------------
*/
#include <printf.h>
#include <alloc.h>
#include <fileio.h>

/* XPCW libraries
   --------------
*/
#include "xpcw.h"
#include "xchrdef.h"

/* Project defs.
   -------------
*/
#define APP_NAME    "PcwFont"
#define APP_VERSION "v1.01 / 17 Nov 2016"
#define APP_COPYRGT "(c) 2015-2016 FloppySoftware"
#define APP_USAGE   "pcwfont -option filename"

/* Main
   ----
*/
int main(argc, argv)
int argc;
unsigned int argv[]; /* char *argv[] */
{
	char *p;

	/* Check arguments */

	p = argv[1];

	if(argc < 2 || (*p != '-' || p[1] == 0 || p[2] != 0))
	{
		usage();
	}

	/* Check if the XPCW RSX is in memory */

	if(!HelloRsx()) {
		error("The XPCW RSX is not in memory");
	}

	/* Run the selected option */

	switch(p[1]) {
		case 'L': /* Load font */
			if(argc != 3) {
				usage();
			}

			load(argv[2]);
			break;
		case 'S': /* Save font */
			if(argc != 3) {
				usage();
			}
			save(argv[2]);
			break;
		default :
			usage();
			break;
	}

	/* Exit */

	return 0;
}

/* Change the internal font from a file
   ------------------------------------
*/
load(fn)
char *fn;
{
	FILE *fp;
	BYTE *buf, *p;
	int i;

	/* Buffer */

	if((buf = p = malloc(2048)) == NULL) {
		no_mem();
	}

	/* Open file */

	if((fp = fopen(fn, "rb")) == NULL) {
		cant_open();
	}

	/* Read font from file */

	if(fread(buf, 2048, 1, fp) != 1) {
		cant_read();
	}

	/* Close file */

	fclose(fp);

	/* Set the internal font */

	for(i = 0; i < 256; ++i) {
		SetChrDef(i, p);

		p += 8;
	}

	/* Free buffer */

	free(buf);
}

/* Save the internal font to a file
   --------------------------------
*/
save(fn)
char *fn;
{
	FILE *fp;
	BYTE *buf, *p;
	int i;

	/* Buffer */

	if((buf = p = malloc(2048)) == NULL) {
		no_mem();
	}

	/* Get the internal font */

	for(i = 0; i < 256; ++i) {
		GetChrDef(i, p);

		p += 8;
	}

	/* Open file */

	if((fp = fopen(fn, "wb")) == NULL) {
		cant_open();
	}

	/* Write font to file */

	if(fwrite(buf, 2048, 1, fp) != 1) {
		cant_write();
	}

	/* Close file */

	if(fclose(fp)) {
		cant_write();
	}

	/* Free buffer */

	free(buf);
}

/* Show usage and exit
   -------------------
*/
usage()
{
	printf("%s %s - %s\n\n", APP_NAME, APP_VERSION, APP_COPYRGT);
	printf("Manage Amstrad PCW fonts.\n\n");
	printf("Usage: pcwfont -option filename\n\n");
	printf("Load font: -L fname\n");
	printf("Save font: -S fname\n");

	exit(0);
}

/* Print error and exit
   --------------------
*/
error(txt)
char *txt;
{
	printf("ERROR: %s.\n", txt);

	exit(1);
}

/* Error: Not enough memory
   ------------------------
*/
no_mem()
{
	error("Not enough memory");
}

/* Error: Can't open file
   ----------------------
*/
cant_open()
{
	error("Can't open file");
}

/* Error: Can't read file
   ----------------------
*/
cant_read()
{
	error("Can't read file");
}

/* Error: Can't write file
   -----------------------
*/
cant_write()
{
	error("Can't write file");
}



