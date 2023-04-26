#include "dsp.h"
#include <memory>
#include <filesystem>
#include <cassert>

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <jack/jack.h>

jack_port_t *input_port;
jack_port_t *output_port;
jack_client_t *client;

double gain = 5.0; // linear

std::unique_ptr<::DSP> model;
std::unordered_map<std::string, double> mNAMParams = {};

double in64[1024];
double out64[1024];

/**
 * The process callback for this JACK application is called in a
 * special realtime thread once for each audio cycle.
 *
 * This client does nothing more than copy data from its input
 * port to its output port. It will exit when stopped by
 * the user (e.g. using Ctrl-C on a unix-ish operating system)
 */
int
process (jack_nframes_t nframes, void *arg)
{
	assert(nframes == 1024);
	// todo: figure out i/o types for jack and nam
        // printf("%u\n", nframes); // 1024 per the jackd server settings

        float *in32, *out32; // 32 bit float per jack client settings

        in32 = (float *) jack_port_get_buffer (input_port, nframes);
        out32 = (float *) jack_port_get_buffer (output_port, nframes);

	// memcpy(out, in, sizeof(jack_default_audio_sample_t) * nframes);

	// convert from float to double on the way in to NAM (may be better to re-write NAM)
	for (int i = 0; i < nframes; i++) {
		in64[i] = (double) in32[i];
	}
	printf("Starting Process\n");
	model->process((double**)&in64, (double**)&out64, 1, nframes, 1.0, 1.0, mNAMParams);
	model->finalize_(nframes);

	// convert from double to float on the way out of NAM
	for (int i = 0; i < nframes; i++) {
		out32[i] = (float) out64[i];
	}

        return 0;
}

/**
 * JACK calls this shutdown_callback if the server ever shuts down or
 * decides to disconnect the client.
 */
void
jack_shutdown (void *arg)
{
        exit (1);
}

int
main (int argc, char *argv[])
{
        const char **ports;
        const char *client_name = "simple";
        const char *server_name = NULL;
        jack_options_t options = JackNullOption;
        jack_status_t status;

	model = get_dsp("/home/patch/Downloads/model.nam");
	model->SetNormalize(true);

        /* open a client connection to the JACK server */

        client = jack_client_open (client_name, options, &status, server_name);
        if (client == NULL) {
                fprintf (stderr, "jack_client_open() failed, "
                         "status = 0x%2.0x\n", status);
                if (status & JackServerFailed) {
                        fprintf (stderr, "Unable to connect to JACK server\n");
                }
                exit (1);
        }
        if (status & JackServerStarted) {
                fprintf (stderr, "JACK server started\n");
        }
        if (status & JackNameNotUnique) {
                client_name = jack_get_client_name(client);
                fprintf (stderr, "unique name `%s' assigned\n", client_name);
        }

        /* tell the JACK server to call `process()' whenever
           there is work to be done.
        */

        jack_set_process_callback (client, process, 0);

        /* tell the JACK server to call `jack_shutdown()' if
           it ever shuts down, either entirely, or if it
           just decides to stop calling us.
        */

        jack_on_shutdown (client, jack_shutdown, 0);

        /* display the current sample rate.
         */

        printf ("engine sample rate: %" PRIu32 "\n",
                jack_get_sample_rate (client));

        /* create two ports */

        input_port = jack_port_register (client, "left_in",
                                         JACK_DEFAULT_AUDIO_TYPE,
                                         JackPortIsInput, 0);
        output_port = jack_port_register (client, "left_out",
                                          JACK_DEFAULT_AUDIO_TYPE,
                                          JackPortIsOutput, 0);

        if ((input_port == NULL) || (output_port == NULL)) {
                fprintf(stderr, "no more JACK ports available\n");
                exit (1);
        }

        /* Tell the JACK server that we are ready to roll.  Our
         * process() callback will start running now. */

        if (jack_activate (client)) {
                fprintf (stderr, "cannot activate client");
                exit (1);
        }

        /* Connect the ports.  You can't do this before the client is
         * activated, because we can't make connections to clients
         * that aren't running.  Note the confusing (but necessary)
         * orientation of the driver backend ports: playback ports are
         * "input" to the backend, and capture ports are "output" from
         * it.
         */

        ports = jack_get_ports (client, NULL, NULL,
                                JackPortIsPhysical|JackPortIsOutput);
        if (ports == NULL) {
                fprintf(stderr, "no physical capture ports\n");
                exit (1);
        }

        if (jack_connect (client, ports[0], jack_port_name (input_port))) {
                fprintf (stderr, "cannot connect input ports\n");
        }

        // printf("%s\n", ports[0]);
        // printf("%s\n", ports[1]);

        free (ports);

        ports = jack_get_ports (client, NULL, NULL,
                                JackPortIsPhysical|JackPortIsInput);
        if (ports == NULL) {
                fprintf(stderr, "no physical playback ports\n");
                exit (1);
        }

        if (jack_connect (client, jack_port_name (output_port), ports[0])) {
                fprintf (stderr, "cannot connect output ports\n");
        }
        if (jack_connect (client, jack_port_name (output_port), ports[1])) {
                fprintf (stderr, "cannot connect output ports\n");
        }

        // printf("%s\n", ports[0]);
        // printf("%s\n", ports[1]);

        free (ports);

        /* keep running until stopped by the user */

        sleep (-1);

        /* this is never reached but if the program
           had some other way to exit besides being killed,
           they would be important to call.
        */

        jack_client_close (client);
        exit (0);
}

