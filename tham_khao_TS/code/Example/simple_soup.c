#include <libsoup/soup.h>
#include <stdio.h>
#include <string.h>
//#include <json-glib/json-glib.h>

int main(int argc, char const *argv[])
{
    SoupSession *session = soup_session_new();
    SoupMessage *msg = soup_message_new("GET", "https://google.com");
    soup_session_send_message(session, msg);
    fwrite(msg->response_body->data,
           1,
           msg->response_body->length,
           stdout);

    printf("\n\n");

    g_object_unref (msg);
    g_object_unref (session);

    // JsonParser *parser = json_parser_new();

    // json_parser_load_from_data(parser, msg->response_body->data, -1, NULL);

    // JsonReader *reader = json_reader_new(json_parser_get_root(parser));

    // json_reader_read_element(reader, 0);

    // json_reader_read_member(reader, "id");
    // int id = json_reader_get_int_value(reader);
    // json_reader_end_member(reader);

    // json_reader_read_member(reader, "type");
    // const char *type = json_reader_get_string_value(reader);
    // json_reader_end_member(reader);

    // json_reader_read_member(reader, "setup");
    // const char *setup = json_reader_get_string_value(reader);
    // json_reader_end_member(reader);

    // json_reader_read_member(reader, "punchline");
    // const char *punchline = json_reader_get_string_value(reader);
    // json_reader_end_member(reader);

    // json_reader_end_element(reader);

    // printf("id = %d, type: %s, setup = %s, punchline = %s\n", id, type, setup, punchline);

    // printf("\n");

    // g_object_unref(reader);
    // g_object_unref(parser);
    return 0;
}