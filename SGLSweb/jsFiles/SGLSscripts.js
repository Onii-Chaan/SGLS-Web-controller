//var totalLamps = Number(prompt("Ievadi lampu daudzumu: "));
var dataType;//izsūtāmo vērtību tips, vai tā ir saskaitīšanās, funkcija vai krāsa
var sendRGBString = "";//nosūtāmā 3 krāsu rgb string vērtība
var rgbw = [0,0,0,0];//šajā sarakstā glabājas 4 krāsu rgbw vērtības
var turnOff = true;//No paša sākuma lampa ir izslēgtā  stāvoklī, tāpēc šis mainīgais arī no sākuma ir true
var picPosition = true; //kad picPosition == true, tad attēls stāv savā sākuma stāvoklī
var buttonOn = false;
var lampNum = "00";//lampu numura String vērtība
var white = "000";//baltās krāsas string vērtība 
var whiteAllowed = false;//atļauj vai arī aizliedz izmantot balto krāsu funkcijās


//ieslēgšanas/izslēgšanas poga
function onOffTextChange(){//nospiežot onOff vai lock pogu, izpildās šī funkcija
    if(turnOff == true){
        turnOff = false;
    } else {
        turnOff = true;
    }
    valueState(turnOff);
}

//slīderis priekš brightness
var slider = document.getElementById("myRange");//saņem vērtību no slīdera 0 - 100
var output = document.getElementById("sliderValueText");//mainīgais slīdera vērtībai, ko izvadīt

output.innerHTML = slider.value;

slider.oninput = function() {//izvada vērtību slīderim
  output.innerHTML = this.value;
}

//colapsed poga
var coll = document.getElementsByClassName("collapsible");

for (var i = 0; i < coll.length; i++) {
  coll[i].addEventListener("click", function() {
    this.classList.toggle("active");
    var content = this.nextElementSibling;
    if (content.style.maxHeight){
      content.style.maxHeight = null;
    } else {
      content.style.maxHeight = content.scrollHeight + "px";
    } 
  });
}

//uzspiežot collapsed pogu attēls uz tās tiek rotēts
function rotateCollapseImg(){
    if(picPosition == true){
        picPosition = false;
        var img=document.getElementById('expandTrianglePic');
        img.setAttribute('style','transform:rotate(180deg)');
    } else {
        picPosition = true;
        var img=document.getElementById('expandTrianglePic');
        img.setAttribute('style','transform:rotate(0deg)');
    }
	
}

function whiteCenter(){
    document.getElementById("whiteCenterBg").style.background = "pink";
    document.getElementById("randomColorBg").style.background = "none";
    document.getElementById("ultraWhiteBg").style.background = "none";
}

function randomColor(){
    document.getElementById("whiteCenterBg").style.background = "none";
    document.getElementById("randomColorBg").style.background = "pink";
    document.getElementById("ultraWhiteBg").style.background = "none";

    for(var i = 0; i<4; i++){
      if(whiteAllowed == true && i == 3 || i<3){//izlaiž white vērtību, ja nebija nospiesta white poga
        rgbw[i] = Math.floor(Math.random()*255);
      }
    }
}

function ultraWhite(){
    document.getElementById("whiteCenterBg").style.background = "none";
    document.getElementById("randomColorBg").style.background = "none";
    document.getElementById("ultraWhiteBg").style.background = "pink";
}

function turnOffBg(){
    document.getElementById("whiteCenterBg").style.background = "none";
    document.getElementById("randomColorBg").style.background = "none";
    document.getElementById("ultraWhiteBg").style.background = "none";
}

function rainbowFunc(){
  turnOffBg();
}

function fadeFunc(){
  turnOffBg();
}

function lmFunc(){
  turnOffBg();
}

function blinkFunc(){
  turnOffBg();
}

function createLampButtons(){
  var lampCount = 12;//////////////////////////////////////////////////////////////////vieta kur ievadīt pogu daudzumu lampām

  for (var i = 1; i<lampCount+1; i++){
    var buttonGen = document.createElement("button");//izveido pogas elementu
    buttonGen.id = "lampButton" + i;
    buttonGen.className = "lampButton";
    var setButtonStyle = document.getElementsByClassName("lampButton");//izveido mainīgo, lai varētu ērti rediģēt dinamisko pogu stilu
    document.getElementsByClassName("dynamicButtonSpace")[0].appendChild(buttonGen);//te atrodas visas lampu pogas

    var lampPar = document.createElement("p");//izveido dinamiski izveidoto pogu teksta elementu
    var innerText = document.createTextNode("L" + i);//izveido tekstu priekš dinamiski izveidotajām pogām
    innerText.id = "lampText" + i;
    innerText.className = "lampText";
    lampPar.appendChild(innerText);

    setButtonStyle[i-1].appendChild(lampPar);

    //Tiek salikts dizains visiem tikko izveidotajiem elementiem
    setButtonStyle[i-1].style.width = "100px";
    setButtonStyle[i-1].style.height = "50px";
    setButtonStyle[i-1].style.marginLeft = "10px";
    setButtonStyle[i-1].style.marginRight = "10px";
    setButtonStyle[i-1].style.marginBottom = "10px";
    setButtonStyle[i-1].style.borderRadius = "7%";
    setButtonStyle[i-1].style.cursor = "pointer";
    setButtonStyle[i-1].style.background = "lightGray";
    setButtonStyle[i-1].style.fontFamily = "Arial, Helvetica, sans-serif";

    document.getElementById("lampButton"+i).addEventListener('click', function lampButton(){lampButtonClick(this);});//katrai no lampu pogām pievieno funkciju kura nosūta pašas pogas vērtību tālāk uz citu funkciju
  }
}


function lampButtonClick(buttonElement){//buttonElement ir veselas pogas vērtība
  var oldLampNum = parseInt(lampNum);
  var buttonChars = ["a", "a"]//tiek definēts char saraksts, kur glabāsies lampu vērtības
  var buttonValueString = "";//saglabā sevī String vērtību par nospiestās pogas numuru
  var buttonText = buttonElement.firstChild.innerHTML;//saņem pogas child elementa vērtību, tekstu, kas ir pogā

  for (var i = 1; i<3;i++){//sadala pogas teksta datus un saliek to masīvā
    var char = buttonText.charAt(i);
    buttonChars[i-1] = char;
  }
  if (buttonChars[1] == ""){//ja skaitlis ir viencipara, tad to pabīda pa labi
    buttonChars[1] = buttonChars[0];
    buttonChars[0] = "0";
  }
  for (var i = 0; i<2; i++){//izveido izsūtāmo String vērtību
    buttonValueString = buttonValueString + buttonChars[i];
  }
  lampNum = buttonValueString;//lampas kārtas numurs

  if(buttonOn == true && oldLampNum == parseInt(lampNum)){//iekrāso pogas pelēkas vai sarkanas atkarībā no tā, kura tiek nospiesta
    buttonElement.style.background = "lightGray";//ja poga bija iepriekš nospiesta un tā tika nospiesta vēlreiz, tad mainās atpakaļ tās krāsa un tiek uzlikta nultā lampa
    buttonOn = false;
    lampNum = "00";
  } else if (buttonOn == false && oldLampNum == parseInt(lampNum)){//ja ir tā pati poga, bet tā iepriekš nebija ieslēgta
    buttonElement.style.background = "red";
    buttonOn = true;
  } else if (oldLampNum != parseInt(lampNum)){//ja tiek nospiesta poga, kura iepriekš nebija nospieta
    if(oldLampNum!=0){
      document.getElementsByClassName("lampButton")[oldLampNum-1].style.background = "lightGray";
    }
    buttonElement.style.background = "red";
    buttonOn = true;
  }
}

function sendValue(sendValueOutput){//parāda nosūtamos datus
  var sendPar = document.getElementById("outputText");//izvada vērtību uz ekrāna
  if(dataType == 1){
    sendPar.innerText = "<" + dataType + lampNum + sendValueOutput + white +">";
  }
}

function valueState(valueStateOutput){//parāda vai dati tiek saņemti vai nosūtīti kā arī citus paziņojumus
  document.getElementById("outputState").innerText = valueStateOutput;
}

function setColor(){//izveido krāsu nosūtamo string vērtību
  dataType = 1;
  var hexToRgb = document.getElementById("colorIn").value.match(/[A-Za-z0-9]{2}/g).map(function(v) { return parseInt(v, 16) }).join(",");//pārveido ievadītās krāsu vērtības no HEX uz RGB
  sendRGBString = "";
  var colorNum = 0;//katru reizi mainās par 1 , lai ieliktu rgbw sarakstā 3 krāsu vērtības
  var colorCount;//nepieciešams, lai izvietotu krāsu ciparu sarakstā vērtības
  var colorChars = [0, 0, 0];//krāsu ciparu saraksts
  var countStr = "";//saglabā krāsu cipara saraksta vērtības, tādējādi izveidojot String skaitli
  
  for(var i = 0; hexToRgb.length>i; i++){//sadala iegūtos rgb datus pa chariem un tad izveido krāsu
    var char = hexToRgb.charAt(i);//sadala rgb krāsu vērtības
    if(char != "," ){
      colorChars[colorNum] = char;//ja programma nesastop komatu string rindiņā, tad pa vienam simbolam tiek pievienots sarakstā
      colorNum++;
    }  
    if(char == "," || i == hexToRgb.length-1){
      switch(colorNum-1){//colorNum-1, jo colorNum vienmēr ir lielāks par 1, jo notiek pirms šī operatora
        case 0://ja skaitlis bija vienciparu
          //"pabīda" ciparus par divām vienībām pa labi
          colorChars[2] = colorChars[0];
          colorChars[0] = 0;
          colorChars[1] = 0;
        break;
        case 1://ja skaitlis bija divciparu
          //"pabīda" ciparus par vienu vienību pa labi
          colorChars[2] = colorChars[1];
          colorChars[1] = colorChars[0];
          colorChars[0] = 0;
        break;
      }
      for (var x = 0; x<3; x++){//saliek krāsu ciparus no sarakasta vienā rindiņā izxveidojot String skaitli
        countStr = countStr + colorChars[x].toString();
      }
      sendRGBString = sendRGBString + countStr;//saliek string skaitļus vienā rindiņā izveidojot izsūtāmo vērtību
      rgbw[colorCount] = parseInt(countStr);
      countStr = "";
      colorNum = 0;
      colorChars = [0, 0, 0];
      colorCount++;
    }
  }
  sendValue(sendRGBString);
}

//izveidot random funkciju līdz galam!!!!
//random izveidos int skaitļus, tāpēc ir jāizveido atsevišķa funkcija, kas izveidotu pareizu, izsūtāmu String vērtību ar visām nepieciešamajām nullēm.
//izsūtāmai String vērtības funkcijai ir jābūt atsvišķai, lai to varētu izmantot arī citas funkcijas. Paraugs: function stringColorSet(r, g, b, w){}

//PĒC RANDOM IZVEIDES UZREIZ IZVEIDOT BALTĀS KRĀSAS IEVADI UN APSTRĀDI. BALTĀ KRĀSA ŠAJĀ SKRIPTĀ IR ĻOTI SVARĪGA!

//Uzspiežot uz baltās krāsas pogas parādās lodziņš , kas prasa norādīt baltās krāsas daudzumu ar slīderi procentos 0-100
//Balto krāsu nosaka atsevišķi. Nospiežot uz baltās krāsas pogas un tad regulējot tās spožumu
//Baltā krāsa arī tiks salikta ciparu sarakstā no kura tiks izveidots String un tas tiks izsūtīts
//Baltās krāsas pogas apkārtesošais aplis pazūd tikai ja tas tiek nospiests vēlreiz vai arī tiek nospiesta gaismas mūzika vai rainbow. Pārējos gadījumos apkārtesošais aplis paliek

//kamēr lampu poga ir uzspiesta tikmēr nedarbojas funkcijas, bet tikai vienas lampas ietvaros pieejamās lietas
//izveidot datu tipa nosūtīšanu funkcijām un atsevišķi arī gaismas mūzikai 

//lai darbotos ar datiem neizmantojot WiFi, ir jāizveido input lodzinš, kur tiks iekšā rakstītas vērtības

//Uzspiežot uz kādas no lampu pogām uzreiz izpildās krāsu nosūtīšana. Ja iepriekš krāsu vērtības netika ievadītas, tad nosūta nulles. Izveidot krāsu vērtības kā publisko String mainīgo

//Brightness vienmēr proporcionāli maina krāsu vērtību, kas nozīmē, ka ja vienu reizi brightness tika uzlikts uz 20%, tad visas tālāk iestatītās krāsas iet caur šo spožuma "filru" katru reizi iestatot krāsu spožumu uz 20%. Tas attiecās uz visām 4 krāsām

//Visas 4 krāsas ir jāievieto String masīvā, arī balto krāsu. To vērtības iegūst izmantojot parseInt()
//Ja baltās krāsas poga netika iestatīta, tad tās vērtība masīvā ir nulle

//Settingos var mainīt paroli

//Ieejot iekšā tiek pieprasīta tikai parole. Ja ievada 3 reizes nepareizi, tad nobloķējas uz 1min (optional)

//random funkcija izvēlās random krāsu vērtības no 0 - 256. 

//izveidot lampu pārskaitīšanās nosūtīšanu

//izveidot funkciju, kas sadalītu lampu skaita vērtību no iekavām un izmantotu to turpmākajā skriptā

//izveidot tā, lai funkcijas darbotos tikai tad, ja on off būls būtu true
