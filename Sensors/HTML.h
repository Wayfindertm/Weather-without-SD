// Block type
const char pageBlockType[] PROGMEM = R"=====(
    <div class="b__name">Type:</div>
    <div class="b__value">
        <select id="[id]_type">
            <option value="11">DHT11</option>
            <option value="21">DHT21</option>
            <option value="22">DHT22</option>
        </select>
    </div>
    <div class="cf"></div>
)=====";

// Block pin
const char pageBlockPin[] PROGMEM = R"=====(
    <div class="b__name">Pin:</div>
    <div class="b__value">
        <select id="[id]_pin">
            <option value="5">D1</option>
            <option value="4">D2</option>
            <option value="2">D4</option>
            <option value="14">D5</option>
            <option value="12">D6</option>
            <option value="13">D7</option>
            <option value="15">D8</option>
        </select>
    </div>
    <div class="cf"></div>
)=====";