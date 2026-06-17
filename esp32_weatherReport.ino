#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <EEPROM.h>


const char* ssid = "KUMARI";
const char* password = "kumari1234";


WebServer server(80);


String lastCity="London";


#define EEPROM_SIZE 100



String getWeather(String city)
{


EEPROM.writeString(0,city);
EEPROM.commit();



HTTPClient geo;


String geoURL =
"https://geocoding-api.open-meteo.com/v1/search?name="
+city+
"&count=1";


geo.begin(geoURL);


geo.GET();


String geoData=geo.getString();



DynamicJsonDocument geoDoc(4096);

deserializeJson(geoDoc,geoData);



float lat =
geoDoc["results"][0]["latitude"];


float lon =
geoDoc["results"][0]["longitude"];



geo.end();




HTTPClient api;



String url =

"https://api.open-meteo.com/v1/forecast?"
"latitude="+String(lat)+
"&longitude="+String(lon)+
"&current=temperature_2m,relative_humidity_2m,wind_speed_10m"
"&daily=temperature_2m_max,temperature_2m_min,weathercode,sunrise,sunset"
"&hourly=relative_humidity_2m"
"&timezone=auto";



api.begin(url);


api.GET();


String data=api.getString();


api.end();



return data;

}





String icon(int code)
{

if(code==0)
return "☀️";

if(code<=3)
return "⛅";

if(code<=67)
return "🌧";

if(code<=77)
return "❄️";

return "⛈";

}





void home()
{


String html=R"rawliteral(

<!DOCTYPE html>

<html>


<head>

<meta charset="UTF-8">

<meta name="viewport" content="width=device-width,initial-scale=1">


<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>



<style>


body{

margin:0;

font-family:Arial;

background:#020617;

color:white;

text-align:center;

}



.container{

max-width:1000px;

margin:auto;

}



.card{

background:#1e293b;

margin:20px;

padding:25px;

border-radius:25px;

}



input{

padding:15px;

border-radius:15px;

border:none;

width:220px;

}



button{

padding:15px;

border-radius:15px;

background:#38bdf8;

border:none;

}



.grid{

display:grid;

grid-template-columns:repeat(auto-fit,minmax(150px,1fr));

gap:15px;

}



.box{

background:#334155;

padding:20px;

border-radius:20px;

}



canvas{

background:white;

border-radius:20px;

margin:20px;

}



</style>


</head>



<body>


<div class="container">


<h1>
ESP32 Global Weather Dashboard
</h1>



<input id="city"
placeholder="Search city">


<button onclick="loadWeather()">
Search
</button>



<div id="data"></div>



<canvas id="temp"></canvas>


<canvas id="humidity"></canvas>



</div>





<script>


let tempChart;
let humChart;



function loadWeather(){


let city=
document.getElementById("city").value;



fetch("/weather?city="+city)

.then(r=>r.json())

.then(d=>{



let c=d.current;



let daily=d.daily;



let icon="🌤";



document.getElementById("data").innerHTML=


`

<div class="card">


<h1>${icon} ${city}</h1>


<h2>
${c.temperature_2m} °C
</h2>


<div class="grid">


<div class="box">

Humidity

<br>

${c.relative_humidity_2m} %

</div>



<div class="box">

Wind

<br>

${c.wind_speed_10m} km/h

</div>




<div class="box">

Sunrise

<br>

${daily.sunrise[0]}

</div>




<div class="box">

Sunset

<br>

${daily.sunset[0]}

</div>


</div>


</div>



<div class="card">

<h2>
7 Day Forecast
</h2>


</div>


`;




if(tempChart)
tempChart.destroy();


tempChart=new Chart(
document.getElementById("temp"),
{

type:"line",

data:{


labels:daily.time,


datasets:[{

label:"Temperature °C",

data:daily.temperature_2m_max

}]


}


});




if(humChart)
humChart.destroy();



humChart=new Chart(

document.getElementById("humidity"),

{


type:"line",


data:{


labels:daily.time,


datasets:[{

label:"Humidity %",

data:d.hourly.relative_humidity_2m.slice(0,7)

}]


}


});



});

}


</script>


</body>

</html>


)rawliteral";



server.send(200,"text/html; charset=UTF-8",html);


}





void weather()
{

String city=
server.arg("city");


String result=
getWeather(city);



server.send(
200,
"application/json; charset=UTF-8",
result
);


}




void setup()
{


Serial.begin(115200);



EEPROM.begin(EEPROM_SIZE);



lastCity=
EEPROM.readString(0);



WiFi.begin(ssid,password);



while(WiFi.status()!=WL_CONNECTED)

{

delay(500);

Serial.print(".");

}



Serial.println();


Serial.print("ESP32 IP:");

Serial.println(WiFi.localIP());



server.on("/",home);


server.on("/weather",weather);



server.begin();


}




void loop()
{

server.handleClient();

}