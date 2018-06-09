/* Settings page save  */
const char sensorsJS[] PROGMEM = R"=====(
<script type="text/javascript">
    var menuItem = document.getElementById("nav").getElementsByClassName("devices")[0];
    menuItem.classList.add("active");
    window.onload = function ()
    {
        document.getElementById("dht1_type").value = [dht1_type];
        document.getElementById("dht1_pin").value = [dht1_pin];
        document.getElementById("dht2_type").value = [dht2_type];
        document.getElementById("dht2_pin").value = [dht2_pin];
        document.getElementById("ds_pin").value = [ds_pin];
        document.getElementById("url").value = "[url]";
    }
    function save(){
        var request = "";
        var elements = document.getElementsByTagName('input');
        for(i=0; i<=elements.length-1; i++) {
            if (request != "") request += "&";
            if (elements[i].type == "checkbox") {
                request += elements[i].id + "=" + (elements[i].checked ? "1" : "0");
            } else {
                request += elements[i].id + "=" + elements[i].value;
            }
        }
        var elements = document.getElementsByTagName('select');
        for(i=0; i<=elements.length-1; i++) {
            if (request != "") request += "&";
            request += elements[i].id + "=" + elements[i].value;
        }
        nanoajax.ajax({url: '/devices/', method: 'POST', body: request}, function (code, response, request) {
            respond(response);
        });
        return false;
    }
</script>
)=====";