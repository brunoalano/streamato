/*
 * Streamato Movie Streaming
 * Copyright (C) 2015  Bruno Alano Medina
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Standard Library */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* GNU LibMicroHttpd Headers */
#include <microhttpd.h>

#define PAGE "<html><head><title>libmicrohttpd demo</title>"\
             "</head><body>libmicrohttpd demo</body></html>"

static int ahc_echo(void * cls,
		    struct MHD_Connection * connection,
		    const char * url,
		    const char * method,
                    const char * version,
		    const char * upload_data,
		    size_t * upload_data_size,
                    void ** ptr) {
  static int dummy;
  const char * page = cls;
  struct MHD_Response * response;
  int ret;

  if (0 != strcmp(method, "GET"))
    return MHD_NO; /* unexpected method */
  if (&dummy != *ptr)
    {
      /* The first time only the headers are valid,
         do not respond in the first round... */
      *ptr = &dummy;
      return MHD_YES;
    }
  if (0 != *upload_data_size)
    return MHD_NO; /* upload data in a GET!? */
  *ptr = NULL; /* clear context pointer */
  response = MHD_create_response_from_data(strlen(page),
					   (void*) page,
					   MHD_NO,
					   MHD_NO);
  ret = MHD_queue_response(connection,
			   MHD_HTTP_OK,
			   response);
  MHD_destroy_response(response);
  return ret;
}

/**
 * Main Block
 *
 * This block needs to create the webserver, and
 * starts the daemon listening to the current directory.
 * 
 * @param  argc number of args
 * @param  argv pointer to array of args
 * @return      operating system return value
 */
int main(void)
{
	/* Store the HTTPD Daemon */
	struct MHD_Daemon * d;

	/* Start the daemon */
	d = MHD_start_daemon(
			MHD_USE_THREAD_PER_CONNECTION, /* Flags */
			5640, /* Port */
			NULL, /* APC */
			NULL, /* APC Params */
			&ahc_echo, /* Handler */
			PAGE, /* Handler Params */
			MHD_OPTION_END);

	/* Check if craeted */
	if ( d == NULL ) return 1;

	/* Debug message */
	printf("\n%s\n", "Started the webserver on port 5640");

	/* Wait for a character */
	(void) getchar();

	/* Debug message */
	printf("Stopping the webserver\n");

	/* Kill the daemon */
	MHD_stop_daemon(d);

  	return 0;
}