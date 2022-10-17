#include <glib.h>
#include <NetworkManager.h>
#include "get_connection.h"

const GPtrArray *devs;
void all_devices_display();

void get_active_ap(NMClient *client, const char *dev_name) {
    NMDevice *dev; // device instantiation pointer
    NMActiveConnection *active_con; // active connection pointer
    NMSettingWireless *s_wireless; // wireless flag setting pointer
    NMConnection *new_connection; // new connection flag pointer
    GBytes *active_ssid; // active ssid val pointer
    const char *name; // name of the device
    const char *ssid; // ssid

    dev = nm_client_get_device_by_iface(client, dev_name);
    active_con = nm_device_get_active_connection(dev);
    new_connection = nm_simple_connection_new_clone(NM_CONNECTION(nm_active_connection_get_connection(active_con)));
    s_wireless = nm_connection_get_setting_wireless(new_connection);
    active_ssid = nm_setting_wireless_get_ssid(s_wireless);
    ssid = nm_utils_ssid_to_utf8((guint8 *)g_bytes_get_data(active_ssid, NULL), g_bytes_get_size(active_ssid));
    g_print("Current active connection of device [%s]: %s \n", dev_name, name);
    g_print("ssid of connection [%s]: %s \n", name, ssid);
}

int main (int argc, char *argv[]) {
    NMClient *client; // client instantiation
    GError *error = NULL; // error flag pointer

    client = nm_client_new (NULL, &error);
    if (!client) {
        g_message("Error: Could not connect to NetworkManager: %s.", error->message); // error handling
        g_error_free(error);
        return 1;
    } else {
        g_print("NetworkManager Version: %s\n", nm_client_get_version(client)); // version display
        devs = nm_client_get_all_devices(client);
        g_ptr_array_foreach (devs, all_devices_display, client);  // list out all the available network devices
    }

    get_active_ap(client, "wlp4s0"); // parameterize the second argument to take interface val (from a .yaml file)

    g_object_unref(client); // unreference the client pointer

    return 0;
}

void all_devices_display() {
    g_print("Network devices: %d\n", devs); // display the network devices
}
