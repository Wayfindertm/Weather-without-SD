/* Reset CSS */
const char resetCSS[] PROGMEM = R"=====(
html,body,div,span,applet,object,iframe,h1,h2,h3,h4,h5,h6,p,blockquote,pre,a,abbr,acronym,address,big,cite,code,del,dfn,em,img,ins,kbd,q,s,samp,small,strike,strong,sub,sup,tt,var,b,u,i,center,dl,dt,dd,ol,ul,li,fieldset,form,label,legend,table,caption,tbody,tfoot,thead,tr,th,td,article,aside,canvas,details,embed,figure,figcaption,footer,header,hgroup,menu,nav,output,ruby,section,summary,time,mark,audio,video{border:0;font-size:100%;font:inherit;vertical-align:baseline;margin:0;padding:0}article,aside,details,figcaption,figure,footer,header,hgroup,menu,nav,section{display:block}body{line-height:1}ol,ul{list-style:none}blockquote,q{quotes:none}blockquote:before,blockquote:after,q:before,q:after{content:none}table{border-collapse:collapse;border-spacing:0}
)=====";

/* Style CSS */
const char styleCSS[] PROGMEM = R"=====(
body {
    position:relative;
    font-size:14px;
    font-family:Verdana,sans-serif;
}
.container {
    max-width:320px;
    margin:10px auto;
    padding:0 10px;
    box-sizing: border-box;
}
a,a:hover {
    color:#00aaff;
}
a {
    text-decoration:none;
}
a:hover {
    text-decoration:underline;
}
button {
    display:table;
    margin:1em auto;
    background:#00aaff;
    color:#ffffff;
    border:none;
    border-radius:4px;
    padding:5px 20px;
    font-size:1.2em;
    outline:0;
}
button:hover {
    background:#0b9de8;
}
button:active {
    background:#0385d0;
}
input[type="text"],input[type="password"],input[type="file"],select {
    display:block;
    width:100%;
    max-width:100%;
    outline:0;
    background:#ffffff;
    border:1px solid #d5dde9;
    padding:3px 5px;
    line-height:1.4em;
    box-sizing:border-box;
    appearance:none;
    -moz-appearance:none;
    -webkit-appearance:none;
}
select {
    padding-right: 30px;
    background: url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAB4AAAAICAMAAADZYb8WAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAAyJpVFh0WE1MOmNvbS5hZG9iZS54bXAAAAAAADw/eHBhY2tldCBiZWdpbj0i77u/IiBpZD0iVzVNME1wQ2VoaUh6cmVTek5UY3prYzlkIj8+IDx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IkFkb2JlIFhNUCBDb3JlIDUuMy1jMDExIDY2LjE0NTY2MSwgMjAxMi8wMi8wNi0xNDo1NjoyNyAgICAgICAgIj4gPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4gPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIgeG1sbnM6eG1wPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvIiB4bWxuczp4bXBNTT0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL21tLyIgeG1sbnM6c3RSZWY9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9zVHlwZS9SZXNvdXJjZVJlZiMiIHhtcDpDcmVhdG9yVG9vbD0iQWRvYmUgUGhvdG9zaG9wIENTNiAoV2luZG93cykiIHhtcE1NOkluc3RhbmNlSUQ9InhtcC5paWQ6REI3QjIxRDJERDNGMTFFNUI0N0E5Rjk3OTQ0NzU3NEUiIHhtcE1NOkRvY3VtZW50SUQ9InhtcC5kaWQ6REI3QjIxRDNERDNGMTFFNUI0N0E5Rjk3OTQ0NzU3NEUiPiA8eG1wTU06RGVyaXZlZEZyb20gc3RSZWY6aW5zdGFuY2VJRD0ieG1wLmlpZDpEQjdCMjFEMEREM0YxMUU1QjQ3QTlGOTc5NDQ3NTc0RSIgc3RSZWY6ZG9jdW1lbnRJRD0ieG1wLmRpZDpEQjdCMjFEMUREM0YxMUU1QjQ3QTlGOTc5NDQ3NTc0RSIvPiA8L3JkZjpEZXNjcmlwdGlvbj4gPC9yZGY6UkRGPiA8L3g6eG1wbWV0YT4gPD94cGFja2V0IGVuZD0iciI/Pqp3l3gAAACHUExURcTw//T8/wC8/wCw/wCv/8jx//X8/wDJ/8rx/wC5/wDE/9n1/6Hp/wC1/wCz/wC2/7vv/xfU/wDI/7bt/wDN/wC2/wDA/wC1/wC2/wDP/932/wDF/17c/wDO/wDA/wDM/03Z/wC9//b9/wC1/wC//wDT/zvY/5vo/wC8/wCz/wC6/wCu/////7ZbWYEAAAAtdFJOU///////////////////////////////////////////////////////////AKXvC/0AAABrSURBVHjadMnJEoIwEATQWCDIchDhELaoxCWx+/+/D6tCBKlKX7pnnqDLIyvo092Nn2JpFX38PBmoPSc9tNtHifywZ04pdP3ts8blpyuTDeybpcV1fW2ZLeQgMTLArAA8GWTe4tffzVmAAQDIkiV4C592OAAAAABJRU5ErkJggg==');
    background-position: 100% 50%;
    background-repeat: no-repeat;
}
input[type="checkbox"] {
    display:none;
}
input[type="checkbox"]+label {
    padding-left:25px;
    position:relative;
}
input[type="checkbox"]+label:before {
    position:absolute;
    left:0;
    top:50%;
    margin-top:-12px;
    content:"";
    height:20px;
    width:20px;
    background:url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACcAAAAQCAYAAACV3GYgAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAAyJpVFh0WE1MOmNvbS5hZG9iZS54bXAAAAAAADw/eHBhY2tldCBiZWdpbj0i77u/IiBpZD0iVzVNME1wQ2VoaUh6cmVTek5UY3prYzlkIj8+IDx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IkFkb2JlIFhNUCBDb3JlIDUuMy1jMDExIDY2LjE0NTY2MSwgMjAxMi8wMi8wNi0xNDo1NjoyNyAgICAgICAgIj4gPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4gPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIgeG1sbnM6eG1wPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvIiB4bWxuczp4bXBNTT0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL21tLyIgeG1sbnM6c3RSZWY9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9zVHlwZS9SZXNvdXJjZVJlZiMiIHhtcDpDcmVhdG9yVG9vbD0iQWRvYmUgUGhvdG9zaG9wIENTNiAoV2luZG93cykiIHhtcE1NOkluc3RhbmNlSUQ9InhtcC5paWQ6NzdDREVEN0JDNzYwMTFFNUFCNzJFNDdFMEU4NENCMDEiIHhtcE1NOkRvY3VtZW50SUQ9InhtcC5kaWQ6NzdDREVEN0NDNzYwMTFFNUFCNzJFNDdFMEU4NENCMDEiPiA8eG1wTU06RGVyaXZlZEZyb20gc3RSZWY6aW5zdGFuY2VJRD0ieG1wLmlpZDo3N0NERUQ3OUM3NjAxMUU1QUI3MkU0N0UwRTg0Q0IwMSIgc3RSZWY6ZG9jdW1lbnRJRD0ieG1wLmRpZDo3N0NERUQ3QUM3NjAxMUU1QUI3MkU0N0UwRTg0Q0IwMSIvPiA8L3JkZjpEZXNjcmlwdGlvbj4gPC9yZGY6UkRGPiA8L3g6eG1wbWV0YT4gPD94cGFja2V0IGVuZD0iciI/PrEZp2QAAAIXSURBVHjatJbPS1RRFMffTFO6TIxyUAOREUnMHCLEleBfIK0GksAg0sW4KEGCNhEEUg24MJAEYXQ3gZug1bSJBtq4EA0nmAaazejIgFFk/pg+93EeXJ/zBu+Dd+DDuXPPfed+74/z5oWsTM3COmEGeiEEdmcdc2J5eAOF2t06g97b+R7DjXPkO4EKPCfX9ulgptaD34ILlrndJOGGS1hM8kUM8hzCdajCB/U8eZMqQRbC0AXFcybrgO/wCa64YllZaDcTFExWysI2ZbdHaV9UotohZSBMWQnmoNVDeMpEGEKaIC/CHHsUlsaBjyM9ahA7MBCmFvgNYlr3MQw74i75ENfomWZt8gTMegi7hluXK+XYP7jDzuciVjB2JJPfw6WlHWXCaU2YOv6vENWe+wNDTpGFAxJXEZ/W+pIIWhBhLbJjurBf0KdXf1DiLot/4eqfRNgy/rOryqtS3UVVpUGLs+8ckz3DPXXF7ruqcg8GlECEqVdTf9DiTpwGAl/inniMK8MtxvyUMSPwO2hxp4zJX+Om67wrB4iV5Pdf98Iccfs+5tw3iSFiHjel7VicvrLr3ik7c+fiPsQNNojFPXbwrSoEfBvseuRzKt3+c16Eh/AKcvIFEfI6IYndhgSs1hlj5+Nyq6+WL3JMIe3IfhBTBXFVy9cvx/4R0Tv6V4nySzBhuHMrMO7xyfQO98Aw3xq5xvSO/wIMAN+9lJylx0I3AAAAAElFTkSuQmCC');
    background-position:0 100%;
    background-repeat:no-repeat;
}
input[type="checkbox"]:checked+label:before {
    background-position:-20px 100%;
}
input:focus, select:focus {
    border-color:#00aaff;
}
input.col4 {
    width:23%;
    margin-right:2.666666%;
    float:left;
    text-align:center;
}
input.col4:last-child {
    margin-right:0;
}
.header {
    font-size:1.4em;
    line-height:2em;
    font-weight:bold;
    text-align:center;
    border-bottom:1px solid #ebebeb;
    margin-bottom:10px;
}
#nav {
    display: table;
    width: 100%;
    margin: 0;
    padding: 0;
    list-style-type: 0;
    border-collapse: collapse;
}
#nav li {
    display: table-cell;
    text-align: center;
    box-sizing: border-box;
    border: 1px solid #00aaff;
}
#nav li a {
    display: block;
    padding: 5px 10px;
}
#nav li a:hover,
#nav li.active a {
    background:#00aaff;
    color: #ffffff;
    text-decoration: none;
}
.block {
    border-bottom:1px solid #ebebeb;
    box-sizing:border-box;
}
.b__header {
    font-size:1.2em;
    line-height:1.4em;
    text-align:center;
    margin-bottom:1em;
}
.cf:after,
.b__content:after {
    content:"";
    display:table;
    clear:left;
}
.b__content .b__name,.b__content .b__value {
    margin-bottom:1em;
    display:block;
    float:left;
}
.b__content .b__name {
    width:100px;
    line-height:calc(1.4em + 6px);
}
.b__content .b__value {
    width:200px;
}
.b__content .b__value label {
    display:inline-block;
    line-height:calc(1.4em + 6px);
    margin-right:10px;
}
.copyright {
    text-align:center;
}
.copyright a {
    display:inline-block;
    margin-top:0.5em;
}
#respond {
    opacity:0;
    padding:5px 10px;
    width:300px;
    box-sizing:border-box;
    position:absolute;
    left:50%;
    margin-left:-150px;
    bottom:80px;
    text-align:center;
    background:#000000;
    background:rgba(0,0,0,0.6);
    color:#ffffff;
    transition:opacity .6s ease-in-out;
    -moz-transition:opacity .6s ease-in-out;
    -webkit-transition: opacity .6s ease-in-out;
}
)=====";