#include <libsoup/soup.h>

int main (int argc, char **argv)
{
    SoupSession *session = soup_session_new ();
    SoupMessageHeaders *response_headers;
    const char *content_type;
    SoupMessage *msg = soup_message_new (SOUP_METHOD_GET, "https://packages.ubuntu.com/ubuntu/logo-ubuntu-header.png");
    GError *error = NULL;
    GBytes *bytes = soup_session_send_and_read (
        session,
        msg,
        NULL, // Pass a GCancellable here if you want to cancel a download
        &error);

    if (error) {
        g_printerr ("Failed to download: %s\n", error->message);
        g_error_free (error);
        g_object_unref (msg);
        g_object_unref (session);
        return 1;
    }

    response_headers = soup_message_get_response_headers (msg);
    content_type = soup_message_headers_get_content_type (response_headers, NULL);

    // content_type = "image/png"
    // bytes contains the raw data that can be used elsewhere
    g_print ("Downloaded %zu bytes of type %s\n",
             g_bytes_get_size (bytes), content_type);

    g_bytes_unref (bytes);
    g_object_unref (msg);
    g_object_unref (session);
    return 0;
}