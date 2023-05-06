#include "webview.h"
#include "lua.h"

static WebKitSettings *rose_webview_get_settings(void)
{
	return webkit_settings_new_with_settings(
		"enable-back-forward-navigation-gestures",
		rose_lua_value_boolean("rose.webview.gestures"),
		"allow-file-access-from-file-urls",
		rose_lua_value_boolean("rose.webview.allow_file_access_from_urls"),
		NULL
	);
}

WebKitWebView *rose_webview_new(void)
{
	WebKitWebView *view = WEBKIT_WEB_VIEW(webkit_web_view_new());
	char *uri = rose_lua_value_string("rose.startpage");

	if (uri == NULL) {
		webkit_web_view_load_uri(view, "https://duckduckgo.com");
	} else {
		webkit_web_view_load_uri(view, uri);
		free(uri);
	}

	webkit_web_view_set_settings(view, rose_webview_get_settings());

	return view;
}