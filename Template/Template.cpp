#include "Template.h"

/*
    Class constructor
*/
Template::Template() {}

/*
    Page compiller
*/
String Template::_page(String title, String header, String content, String scripts, bool home = false) {
    String _content = (String)page;
    _content.replace("[title]",title);
    _content.replace("[header]",header);
    _content.replace("[content]",content);
    _content.replace("[scripts]",scripts);
    _content.replace("[footer_link]",(home ? "/admin/" : "/"));
    _content.replace("[footer_title]",(home ? "Admin page" : "Home page"));
    return _content;
}

/*
    Page block compiller
*/
String Template::_pageBlock(String header, String content) {
    String _content = (String)pageBlock;
    _content.replace("[header]",header);
    _content.replace("[content]",content);
    return _content;
}

/*
    Input block compiller
*/
String Template::_inputBlock(String header, String id, String value, bool disabled = false) {
    String _content = (String)pageBlockInput;
    _content.replace("[header]",header);
    _content.replace("[id]",id);
    _content.replace("[value]",value);
    _content.replace("[disabled]",(disabled ? "disabled" : ""));
    return _content;
}

/*
    Checkbox block compiller
*/
String Template::_checkboxBlock(String header, String id, bool value) {
    String _content = (String)pageBlockCheckbox;
    _content.replace("[header]",header);
    _content.replace("[id]",id);
    _content.replace("[value]",(value ? "checked" : ""));
    return _content;
}

/*
    IP block compiller
*/
String Template::_ipBlock(String header, String id, byte value[]) {
    String _content = (String)pageBlockIP;
    _content.replace("[header]",header);
    _content.replace("[id]",id);
    for(int i=0; i<4; i++) {
        _content.replace("[value_"+(String)i+"]",(String)value[i]);
    }
    return _content;
}

/*
    Home page
*/
String Template::homeHandler(String content) {

    // Uptime
    String _uptime = "";
    uint32_t time = millis()/1000;
    _uptime = ":" + ((time % 60) < 10 ? "0"+(String)(time % 60) : (time % 60));
    time /= 60;
    _uptime =  ":" + ((time % 60) < 10 ? "0"+(String)(time % 60) : (time % 60)) + _uptime;
    time /= 60;
    _uptime = (String)(time % 24) + _uptime;
    time /= 24;
    _uptime = (String)time + " days " + _uptime;

    // Memory
    String _memory = (String)ESP.getFreeHeap();

    // Uptime block
    String _uptimeBlock = _inputBlock("Uptime:","uptime",_uptime, true);

    // Memory block
    String _memoryBlock = _inputBlock("Memory:","memory",_memory, true);

    // Page content
    String _pageContent = "";
    _pageContent += _uptimeBlock;
    _pageContent += _memoryBlock;
    _pageContent = _pageBlock("System:",_pageContent);
    _pageContent += content;


    // Compile page
    return _page(
        "Home page",    // Title
        "Status",  		// Header
        _pageContent,   // Page content
        "",             // Scripts
        true            // IS home page
    );

}

/*
    Admin page
*/
String Template::adminHandler(Config *config) {

    // Page content
    String _pageContent = "";

    // Add menu
    _pageContent += (String)pageMenu;

    // Add auth settings block
    String _authContent = "";
    _authContent += _inputBlock("Login:","auth_login",config->auth_login);
    _authContent += _inputBlock("Password:","auth_pass",config->auth_pass);
    _pageContent += _pageBlock("Auth settings",_authContent);

    // WiFi settings
    String _wifiContent = "";
    _wifiContent += _checkboxBlock("AP mode:","ap_mode",config->ap_mode);
    _wifiContent += _inputBlock("SSID:","ap_ssid",config->ap_ssid);
    _wifiContent += _inputBlock("Password:","ap_pass",config->ap_pass);
    _wifiContent += _ipBlock("IP:","ip",config->ip);
    _wifiContent += _ipBlock("Mask:","mask",config->mask);
    _wifiContent += _ipBlock("GW:","gw",config->gw);
    _wifiContent += _checkboxBlock("DHCP:","dhcp",config->dhcp);
    _pageContent += _pageBlock("WiFi settings",_wifiContent);

    // Save button
    _pageContent += (String)pageBlockBtn;

    // Compile page
    return _page(
        "Settings",         // Title
        "System settings",  // Header
        _pageContent,       // Page content
        adminJS             // Scripts
    );

}

/*
    Firmware page
*/
String Template::firmwareHandler() {

    // Page content
    String _pageContent = "";

    _pageContent += (String)pageMenu;
    _pageContent += (String)pageBlockUpdate;

    // Compile page
    return _page(
        "Firmware",         // Title
        "Firmware update",  // Header
        _pageContent,       // Page content
        firmwareJS          // Scripts
    );

}