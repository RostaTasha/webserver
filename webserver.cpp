#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

uv_loop_t *  loop;
sockaddr_in addr;

#define DEFAULT_PORT 80
#define DEFAULT_BACKLOG "./log.txt"

void read_cb(uv_stream_t* tcp, ssize_t nread, const uv_buf_t * buf) {
 size_t parsed;

if (nread<0){
   uv_err_t err = uv_last_error(uv_loop);
   if (err.code != UV_EOF) {
      UVERR(err, "read");
}


 uv_tcp_t* client = (uv_tcp_t*) tcp->data;

 
 if (nread >= 0) {
  parsed = http_parser_execute(
  &client->parser, &parser_settings, buf.base, nread);
    if (parsed < nread) {
      LOG_ERROR("parse error");
      uv_close((uv_handle_t*) &client->handle, on_close);
    }
  } else {

    }
  }

  free(buf.base);

}


void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    *buf = uv_buf_init((char*) malloc(suggested_size), suggested_size);
}


void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }

    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        uv_read_start((uv_stream_t*) client, alloc_buffer, read_cb);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}




int main() {
    loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &addr);

    uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
    int r = uv_listen((uv_stream_t*) &server, DEFAULT_BACKLOG, on_new_connection);
    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }
    return uv_run(loop, UV_RUN_DEFAULT);
}