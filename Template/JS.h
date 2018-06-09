/* Nano AJAX */
const char scripts[] PROGMEM = R"=====(
/* NanoAjax */
!function(e,t){function n(e){return e&&t.XDomainRequest&&!/MSIE 1/.test(navigator.userAgent)?new XDomainRequest:t.XMLHttpRequest?new XMLHttpRequest:void 0}function o(e,t,n){e[t]=e[t]||n}var r=["responseType","withCredentials","timeout","onprogress"];e.ajax=function(e,a){function u(e,t){return function(){c||a(void 0===f.status?e:f.status,f.response||f.responseText||t,f),c=!0}}var s=e.headers||{},i=e.body,d=e.method||(i?"POST":"GET"),c=!1,f=n(e.cors);f.open(d,e.url,!0);var l=f.onload=u(200);f.onreadystatechange=function(){4===f.readyState&&l()},f.onerror=u(null,"Error"),f.ontimeout=u(null,"Timeout"),f.onabort=u(null,"Abort"),i&&(o(s,"X-Requested-With","XMLHttpRequest"),t.FormData&&i instanceof t.FormData||o(s,"Content-Type","application/x-www-form-urlencoded"));for(var p,m=0,v=r.length;v>m;m++)p=r[m],void 0!==e[p]&&(f[p]=e[p]);for(var p in s)f.setRequestHeader(p,s[p]);return f.send(i),f},t.nanoajax=e}({},function(){return this}());

/* Respond */
function respond(json) {
    var data = JSON.parse(json);
    var text = "";
    if ( data.success == "true" ) text = "Options saved!<br>Rebooting device.";
    else text = "Error: " + data.message;
    var el = document.getElementById('respond');
    if ( text ) el.innerHTML = text;
    el.style.opacity = 1;
    setTimeout(function() { el.style.opacity = 0 }, 1500);
    setTimeout(function() { location.reload() }, 5000);
}
)=====";

/* Main admin page javascript  */
const char adminJS[] PROGMEM = R"=====(
<script type="text/javascript">
    var menuItem = document.getElementById("nav").getElementsByClassName("admin")[0];
    menuItem.classList.add("active");
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
        nanoajax.ajax({url: '/admin/', method: 'POST', body: request}, function (code, response, request) {
            respond(response);
        });
        return false;
    }
</script>
)=====";

/* Main admin page javascript  */
const char firmwareJS[] PROGMEM = R"=====(
<script type="text/javascript">
    var menuItem = document.getElementById("nav").getElementsByClassName("firmware")[0];
    menuItem.classList.add("active");
</script>
)=====";