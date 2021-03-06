char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    body, table {
      text-align: center;
      font-family: "Trebuchet MS", Arial;
      margin-left:auto;
      margin-right:auto;
    }
    .slider {
      width: 300px;
    }
  img {
    width: 200px;
  }
  </style>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
</head>
<body>
  <img src="https://www.fablab-luebeck.de/user/pages/01.home/_wedsgn/fablabLogo.png">
  <h1>Roboarm - Controll</h1>
  <p>Endeffektor Position: <span id="upperServoPos"></span></p>
  <input type="range" min="10" max="170" class="slider" id="upperServoSlider" onchange="servo(this.value, 'upper')"/>

  <p>Mittlerer Arm Position: <span id="middleServoPos"></span></p>
  <input type="range" min="10" max="170" class="slider" id="middleServoSlider" onchange="servo(this.value, 'middle')"/>

  <p>Unterer Arm Position: <span id="lowerServoPos"></span></p>
  <input type="range" min="10" max="170" class="slider" id="lowerServoSlider" onchange="servo(this.value, 'lower')"/>

  <p>Basis Position: <span id="baseServoPos"></span></p>
  <input type="range" min="10" max="170" class="slider" id="baseServoSlider" onchange="servo(this.value, 'base')"/>
  <script>
    var upperSlider = document.getElementById("upperServoSlider");
    var upperServoP = document.getElementById("upperServoPos");
  
  var middleSlider = document.getElementById("middleServoSlider");
    var middleServoP = document.getElementById("middleServoPos");
  
  var lowerSlider = document.getElementById("lowerServoSlider");
    var lowerServoP = document.getElementById("lowerServoPos");
  
  var baseSlider = document.getElementById("baseServoSlider");
    var baseServoP = document.getElementById("baseServoPos");
    
    upperServoP.innerHTML = upperSlider.value;
  middleServoP.innerHTML = middleSlider.value;
  lowerServoP.innerHTML = lowerSlider.value;
  baseServoP.innerHTML = baseSlider.value;
    
    upperSlider.oninput = function() {
      upperSlider.value = this.value;
      upperServoP.innerHTML = this.value;
    }
  
    middleSlider.oninput = function() {
      middleSlider.value = this.value;
      middleServoP.innerHTML = this.value;
    }

    lowerSlider.oninput = function() {
      lowerSlider.value = this.value;
      lowerServoP.innerHTML = this.value;
    }

    baseSlider.oninput = function() {
      baseSlider.value = this.value;
      baseServoP.innerHTML = this.value;
    } 
    
    $.ajaxSetup({timeout:1000});
    
    function servo(pos, part) {
      var xhttp = new XMLHttpRequest();
      if(part == 'base'){
        xhttp.open("GET", "setValue?baseServoPos="+pos + "&", true);
      }
      if(part == 'lower'){
        xhttp.open("GET", "setValue?lowerArmServoPos="+pos + "&", true);
      }
      if(part == 'middle'){
        xhttp.open("GET", "setValue?middleArmServoPos="+pos + "&", true);
      }
      if(part == 'upper'){
        xhttp.open("GET", "setValue?upperArmServoPos="+pos + "&", true);
      }
      
      
      xhttp.send();
    }    
  </script>
</body>
</html>
)=====";
