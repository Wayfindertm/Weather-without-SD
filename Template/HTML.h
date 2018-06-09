 // Page template
const char page[] PROGMEM = R"=====(
    <!DOCTYPE html>
    <html>
        <head>
            <meta name="viewport" content="width=device-width, initial-scale=1"/>
            <meta charset="utf-8">
            <title>[title]</title>
            <link rel="stylesheet" href="/reset.css">
            <link rel="stylesheet" href="/style.css">
        </head>
        <body>
            <div class="header">
                <div class="container">[header]</div>
            </div>
            [content]
            <div class="copyright">
                <div class="container">
                    <a href="[footer_link]">[footer_title]</a><br><br>
                    &copy; <a target="_blank" href="http://luway.ru/">LuWay</a>. 2016
                </div>
            </div>
        </body>
        <script type="text/javascript" src="/scripts.js"></script>
        [scripts]
    </html>
)=====";

// Menu template
const char pageMenu[] PROGMEM = R"=====(
    <div class="container">
        <ul id="nav">
            <li class="admin"><a href="/admin/">Admin</a></li>
            <li class="devices"><a href="/devices/">Devices</a></li>
            <li class="firmware"><a href="/firmware/">Firmware</a></li>
        </ul>
    </div>
)=====";

// Block template
const char pageBlock[] PROGMEM = R"=====(
    <div class="block">
        <div class="container">
            <div class="b__header">[header]</div>
            <div class="b__content">
                [content]
            </div>
        </div>
    </div>
)=====";

// Block input
const char pageBlockInput[] PROGMEM = R"=====(
    <div class="b__name">[header]</div>
    <div class="b__value">
        <input type="text" id="[id]" value="[value]" [disabled]>
    </div>
    <div class="cf"></div>
)=====";

// Block IP
const char pageBlockIP[] PROGMEM = R"=====(
    <div class="b__name">[header]</div>
    <div class="b__value">
        <input type="text" id="[id]_0" class="col4" value="[value_0]">
        <input type="text" id="[id]_1" class="col4" value="[value_1]">
        <input type="text" id="[id]_2" class="col4" value="[value_2]">
        <input type="text" id="[id]_3" class="col4" value="[value_3]">
    </div>
    <div class="cf"></div>
)=====";

// Block checkbox
const char pageBlockCheckbox[] PROGMEM = R"=====(
    <div class="b__name">[header]</div>
    <div class="b__value">
        <input type="checkbox" id="[id]" [value]>
        <label for="[id]" >On/Off</label>
    </div>
    <div class="cf"></div>
)=====";

// Block save button
const char pageBlockBtn[] PROGMEM = R"=====(
    <button onclick="save();">Save</button>
    <div id="respond"></div>
)=====";

// Block update form
const char pageBlockUpdate[] PROGMEM = R"=====(
    <form method="POST" action="/fwupdate" enctype="multipart/form-data">
        <div class="block">
            <div class="container">
                <div class="b__content">
                    <div class="b__name">File:</div>
                    <div class="b__value">
                        <input type="file" name="update">
                    </div>
                </div>
            </div>
        </div>
        <button>Update</button>
        <div id="respond"></div>
    </form>
)=====";