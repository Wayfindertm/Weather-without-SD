#include "Sensors.h"

// Class constructor
Sensors::Sensors() {}

// Init config
void Sensors::setup() {

    DEBUG_PRINT_SENSORS("Load config.");

    // Load config
    if (!read()) {
        DEBUG_PRINT_SENSORS("Write default config file.");
        save();
    }

    DEBUG_PRINT_SENSORS("Config loaded.");

    if(config.dht1_en) {
        DEBUG_PRINT_SENSORS("Init DHT1 sensor.");
        _dht1 = new DHT(config.dht1_pin, config.dht1_type);
        _dht1->begin();
    }
    if(config.dht2_en) {
        DEBUG_PRINT_SENSORS("Init DHT2 sensor.");
        _dht2 = new DHT(config.dht2_pin, config.dht2_type);
        _dht2->begin();
    }
    if(config.ds_en) {
        DEBUG_PRINT_SENSORS("Init DS18x20 sensor.");
        _onewire = new OneWire(config.ds_pin);
        _ds.setOneWire(_onewire);
        _ds.begin();
    }

    DEBUG_PRINT_SENSORS("Ready.");
    DEBUG_PRINT_LN();

}

// Read config from SPIFFS
bool Sensors::read(){

    // Try open SPIFFS configvoid
    File configFile = SPIFFS.open("/sensors.json", "r");
    if (!configFile) {
        DEBUG_PRINT_SENSORS("Failed to open config file.");
        return false;
    }

    // Check config file size
    size_t size = configFile.size();
    if (size > 1024) {
        DEBUG_PRINT_SENSORS("Config file size is too large.");
        return false;
    }

    // Try parse config
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<1024> jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(buf.get());

    if (!json.success()) {
        DEBUG_PRINT_SENSORS("Failed to parse config file.");
        return false;
    }

    // Load DHT 1 settings
    config.dht1_en      = json["dht1_en"];
    config.dht1_pin     = json["dht1_pin"];
    config.dht1_type    = json["dht1_type"];

    // Load DHT 2 settings
    config.dht2_en      = json["dht2_en"];
    config.dht2_pin     = json["dht2_pin"];
    config.dht2_type    = json["dht2_type"];

    // Load DS18x20 settings
    config.ds_en      = json["ds_en"];
    config.ds_pin     = json["ds_pin"];

    // Url
    config.url        = json["url"].asString();

    configFile.close();
    return true;
}

// Save configto SPIFFS
bool Sensors::save() {

    // Try to open file for writing
    File configFile = SPIFFS.open("/sensors.json", "w");
    if (!configFile) {
        DEBUG_PRINT_SENSORS("Failed to open config file for writing.");
        return false;
    }

    StaticJsonBuffer<1024> jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();

    json["dht1_en"]     = config.dht1_en;
    json["dht1_pin"]    = config.dht1_pin;
    json["dht1_type"]   = config.dht1_type;

    json["dht2_en"]     = config.dht2_en;
    json["dht2_pin"]    = config.dht2_pin;
    json["dht2_type"]   = config.dht2_type;

    json["ds_en"]       = config.ds_en;
    json["ds_pin"]      = config.ds_pin;

    json["url"]         = config.url.c_str();

    json.printTo(configFile);
    configFile.close();
    return true;
}

/*
    Type block compiller
*/
String Sensors::_typeBlock(String id) {
    String _content = (String)pageBlockType;
    _content.replace("[id]",id);
    return _content;
}

/*
    Pin block compiller
*/
String Sensors::_pinBlock(String id) {
    String _content = (String)pageBlockPin;
    _content.replace("[id]",id);
    return _content;
}

/*
    Sensors Home page data
*/
String Sensors::homeHandler(Template *TPL) {

    // No sensors
    if(!config.dht1_en && !config.dht2_en && !config.ds_en) return "";

    // Page content
    String _pageContent = "";

    if(config.dht1_en) {
        _pageContent += TPL->_inputBlock("DHT1 temp:","dht1_temp",(String)_dht1_temp, true);
        _pageContent += TPL->_inputBlock("DHT1 hum:","dht1_hum",(String)_dht1_hum, true);
    }
    if(config.dht2_en) {
        _pageContent += TPL->_inputBlock("DHT2 temp:","dht2_temp",(String)_dht2_temp, true);
        _pageContent += TPL->_inputBlock("DHT2 hum:","dht2_hum",(String)_dht2_hum, true);
    }
    if(config.ds_en) {
        _pageContent += TPL->_inputBlock("DS temp:","ds_temp",(String)_ds_temp, true);
    }

    _pageContent = TPL->_pageBlock("Sensors",_pageContent);

    return _pageContent;
}


/*
    Sensors admin page
*/
String Sensors::sensorsHandler(Template *TPL) {

    // Page content
    String _pageContent = "";

    // Add menu
    _pageContent += (String)pageMenu;

    // Add DHT1 settings block
    String _dht1Content = "";
    _dht1Content += TPL->_checkboxBlock("Enable:","dht1_en",config.dht1_en);
    _dht1Content += _typeBlock("dht1");
    _dht1Content += _pinBlock("dht1");
    _pageContent += TPL->_pageBlock("DHT1 settings",_dht1Content);

    // Add DHT2 settings block
    String _dht2Content = "";
    _dht2Content += TPL->_checkboxBlock("Enable:","dht2_en",config.dht2_en);
    _dht2Content += _typeBlock("dht2");
    _dht2Content += _pinBlock("dht2");
    _pageContent += TPL->_pageBlock("DHT2 settings",_dht2Content);

    // Add DS settings block
    String _dsContent = "";
    _dsContent += TPL->_checkboxBlock("Enable:","ds_en",config.ds_en);
    _dsContent += _pinBlock("ds");
    _pageContent += TPL->_pageBlock("DS settings",_dsContent);

    // Add URL settings block
    String _urlContent = "";
    _urlContent += TPL->_inputBlock("URL:","url",config.url,false);
    _pageContent += TPL->_pageBlock("URL settings",_urlContent);

    // Save button
    _pageContent += (String)pageBlockBtn;

    // JavaScript
    String _pageJS = (String)sensorsJS;
    _pageJS.replace("[dht1_type]", (String)config.dht1_type);
    _pageJS.replace("[dht1_pin]", (String)config.dht1_pin);
    _pageJS.replace("[dht2_type]", (String)config.dht2_type);
    _pageJS.replace("[dht2_pin]", (String)config.dht2_pin);
    _pageJS.replace("[ds_pin]", (String)config.ds_pin);
    _pageJS.replace("[url]", config.url);

    // Compile page
    return TPL->_page(
        "Sensors",          // Title
        "Sensors settings", // Header
        _pageContent,       // Page content
        _pageJS,         	// Scripts
        false
    );

}

/*
    Sensors admin page save
*/
void Sensors::saveHandler(ESP8266WebServer *server) {

    config.dht1_en = false;
    config.dht2_en = false;
    config.ds_en   = false;
    for ( uint8_t i = 0; i < server->args(); i++ ) {

        // DHT 1 settings
        if(server->argName(i)=="dht1_en" && server->arg(i)=="1") config.dht1_en = true;
        if(server->argName(i)=="dht1_type") config.dht1_type = server->arg(i).toInt();
        if(server->argName(i)=="dht1_pin") config.dht1_pin = server->arg(i).toInt();

        // DHT 2 settings
        if(server->argName(i)=="dht2_en" && server->arg(i)=="1") config.dht2_en = true;
        if(server->argName(i)=="dht2_type") config.dht2_type = server->arg(i).toInt();
        if(server->argName(i)=="dht2_pin") config.dht2_pin = server->arg(i).toInt();

        // DS18x20 settings
        if(server->argName(i)=="ds_en" && server->arg(i)=="1") config.ds_en = true;
        if(server->argName(i)=="ds_pin") config.ds_pin = server->arg(i).toInt();

        // Url settings
        if(server->argName(i)=="url") config.url = server->arg(i);

    }
    save();
}

/*
    Sensors json handler
*/
String Sensors::jsonHandler() {

    String retJSON;
    StaticJsonBuffer<512> jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();

    if(!config.dht1_en && !config.dht2_en && !config.ds_en){
        json["success"] = false;
    } else {
        json["success"] = true;
        JsonObject& list = json.createNestedObject("list");

        if(config.dht1_en) {
            list["dht1_temp"] = _dht1_temp;
            list["dht1_hum"] = _dht1_hum;
        }

        if(config.dht2_en) {
            list["dht2_temp"] = _dht2_temp;
            list["dht2_hum"] = _dht2_hum;
        }

        if(config.ds_en) {
            list["ds_temp"] = _ds_temp;
        }
    };

    json.printTo(retJSON);

    return retJSON;
}

/*
    Reading temp loop handle
*/
void Sensors::handle() {
    unsigned long currentMillis = millis();
    if(currentMillis - _previousMillis >= _interval) {
        _previousMillis = currentMillis;

        float temp, hum;

        if(config.dht1_en) {
            temp = _dht1->readTemperature();
            hum  = _dht1->readHumidity();
            if (!isnan(temp) && !isnan(hum)) {
                _dht1_temp = temp;
                _dht1_hum  = hum;
            }
        }

        if(config.dht2_en) {
            temp = _dht2->readTemperature();
            hum  = _dht2->readHumidity();
            if (!isnan(temp) && !isnan(hum)) {
                _dht2_temp = temp;
                _dht2_hum  = hum;
            }
        }

        if(config.ds_en) {
            if (_ds.requestTemperaturesByIndex(0)){
                _ds_temp = _ds.getTempCByIndex(0);
            }
        }

    }
}

/*
    HTTP send loop handle
*/
void Sensors::HTTPhandle() {
    unsigned long currentMillis = millis();
    if(currentMillis - _httpMillis >= _httpinterval) {
        _httpMillis = currentMillis;

        // Send data to server
        _http.begin(config.url + urldecode(jsonHandler()));

        int httpCode = _http.GET();
        DEBUG_PRINT_SENSORS("[HTTP] Send data code: "+(String)httpCode);

        _http.end();

    }
}

unsigned char Sensors::h2int(char c)
{
    if (c >= '0' && c <='9'){
        return((unsigned char)c - '0');
    }
    if (c >= 'a' && c <='f'){
        return((unsigned char)c - 'a' + 10);
    }
    if (c >= 'A' && c <='F'){
        return((unsigned char)c - 'A' + 10);
    }
    return(0);
}
String Sensors::urldecode(String str)
{

    String encodedString="";
    char c;
    char code0;
    char code1;
    for (int i =0; i < str.length(); i++){
        c=str.charAt(i);
      if (c == '+'){
        encodedString+=' ';
      }else if (c == '%') {
        i++;
        code0=str.charAt(i);
        i++;
        code1=str.charAt(i);
        c = (h2int(code0) << 4) | h2int(code1);
        encodedString+=c;
      } else{

        encodedString+=c;
      }

      yield();
    }

   return encodedString;
}