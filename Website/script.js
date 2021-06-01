client = new Paho.MQTT.Client("mqtt.netpie.io", 443, 'a4f712e9-1d5f-43cb-b081-f981bcfea3a3');
client.onMessageArrived = onMessageArrived;

var options = {
  useSSL: true,
  userName : "G89LPX5BqJHh8MfHtke76RwpnhzkMVKc",
  password : "*w3naBKjhe7OWz6JgVmliB3CpE13oTC5",  
  onSuccess: onConnect,
  onFailure: doFail,
}

client.connect(options);

function onConnect() {
  client.subscribe("@msg/temp");
  console.log('Connected!');
}

function doFail(e){
    console.log(e);
  }

function onMessageArrived(message) {
  var received_string = message.payloadString;
  setGaugeValue(gaugeElement, received_string/100);
//  received_string = 100 - received_string;
//  received_string = received_string + "%";
  
  //document.getElementById("description").innerHTML = received_string;
}

const gaugeElement = document.querySelector(".gauge");

function setGaugeValue(gauge, value) {
  if (value < 0 || value > 1) {
    return;
  }

  gauge.querySelector(".gauge__fill").style.transform = `rotate(${
    value / 2
  }turn)`;
  gauge.querySelector(".gauge__cover").textContent = `${Math.round(
    value * 100
  )}%`;
}

setGaugeValue(gaugeElement, 0);