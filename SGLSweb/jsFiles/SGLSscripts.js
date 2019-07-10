//var totalLamps = Number(prompt("Ievadi lampu daudzumu: "));
var lampButtonPressed = "#9ab8a0";//dinamisko pogu krasa kad ta tika nospiesta
var lampButtonDefault = "#6c8270";//dinamisko pogu krasa kad ta nav nospiesta

var dataType;//izsūtāmo vērtību tips, vai tā ir saskaitīšanās, funkcija vai krāsa
var sendRGBString = "";//nosūtāmā 3 krāsu rgb string vērtība
var rgbw = [0,0,0,0];//šajā sarakstā glabājas 4 krāsu rgbw vērtības
var turnOff = true;//No paša sākuma lampa ir izslēgtā  stāvoklī, tāpēc šis mainīgais arī no sākuma ir true
var buttonOn = false;//norada vai lietotajs darbojas ap vienu lampu vai ap visam kopa, tiek izmantots, lai nevaretu ieslegt funkcijas kad darbojas ap vienu lampu
var lampNum = "00";//lampu numura String vērtība
var whiteAllowed = false;//atļauj vai arī aizliedz izmantot balto krāsu funkcijās
var funcNum = 0;//lampu funkcijas numurs
//document.getElementsByClassName("hidable")[0].style.display = "none"; BOOKMARK1

//ieslēgšanas/izslēgšanas poga
function onOffTextChange(){//nospiežot onOff vai lock pogu, izpildās šī funkcija
    if(turnOff == true && whiteSetOn == false){
        turnOff = false;
        //document.getElementsByClassName("hidable")[0].style.display = "block"; BOOKMARK1
        dataType = 0;
    } else {
        turnOff = true;
        //document.getElementsByClassName("hidable")[0].style.display = "none"; BOOKMARK1
    }
    dataType = 2;
    funcNum = 0;
    sendValue(funcNumBuilder(funcNum))
    valueState(turnOff);
}

//slīderis priekš brightness
var slider = document.getElementById("myRange");//saņem vērtību no slīdera 0 - 100
var output = document.getElementById("sliderValueText");//mainīgais slīdera vērtībai, ko izvadīt
output.innerHTML = slider.value;

slider.oninput = function() {//izvada vērtību slīderim
  if(turnOff==false){
    output.innerHTML = this.value;
  }
}

slider.onmouseup = function(){//uzstada slideri atpakal uz 100% kad tas tiek atlaists
  if(turnOff==false){
    setBrightness(this.value);
    slider.value = 100;
    output.innerHTML = 100;
  }
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
 
      var picRotate = document.getElementsByClassName("rotatePic")[i].style;
      valueState(picRotate);

  });
}


var picPosition = true; //kad picPosition == true, tad attēls stāv savā sākuma stāvoklī
//uzspiežot collapsed pogu attēls uz tās tiek rotēts
function rotateCollapseImg(image){
    if(picPosition == true){
        picPosition = false;
        image[0].setAttribute('style','transform:rotate(180deg)');
    } else {
        picPosition = true;
        image[0].setAttribute('style','transform:rotate(0deg)');
    }
}

var whiteSetOn = false; //norada vai ap baltas krasas ievadi var darboties kad pareja lapa nedarbojas
function whiteCenter(){//Parada baltas krasas ievades logu
  if(turnOff==false){
    document.getElementsByClassName("whiteCenterDiv")[0].style.display = "block";
    turnOff = true;
    whiteSetOn = true;
  }
}

//slideris prieks white brightness
var newWhite = 100;//saglaba sevi baltas krasas vertibu, pasa sakuma vertiba ir uzlikta uz maksimumu

var whiteSlider = document.getElementById("whiteRange");//saņem vērtību no balta līdera 0 - 100
var whiteSliderOutput = document.getElementById("whiteBrightnessSliderTextValue");//mainīgais baltajai slīdera vērtībai, ko izvadīt
output.innerHTML = whiteSlider.value;
whiteSlider.oninput = function() {//izvada vērtību slīderim
  if(whiteSetOn == true){
      whiteSliderOutput.innerHTML = this.value;
      if(isNaN(this.value)==false){
        newWhite = this.value;//Tiek iestatita baltas krasas vertiba
      }
    }
}

function okWhite(){//aprekina un iestata baltas krasas vertibu
  if(whiteSetOn == true){
    document.getElementsByClassName("whiteCenterDiv")[0].style.display = "none";
    rgbw[3] = scaleToRange(newWhite, 0, 100, 0, 255);//Parveido procentus par viena baita vertibu
    if(rgbw[3]>0){//Nosaka vai balta krasa ir ieslegta vai ari nav
      whiteAllowed = true;
    } else {
      whiteAllowed = false;
    }
    dataType = 1;
    stringColorSet();//iestata parejas krasas un izvada vertibas
    whiteSetOn = false;
    turnOff = false;
  }
}

function cancelWhite(){//iziet ara no baltas krasas iestatisanas lodzina nemainot nekadas vertibas
  if(whiteSetOn == true){
    document.getElementsByClassName("whiteCenterDiv")[0].style.display = "none";
    whiteSetOn = false;
    turnOff = false;
  }
}

function scaleToRange(number, fromMin, fromHigh, toMin, toHigh){//Si funkcija parveido skaitli no vienas kopas uz citu
  return Math.round(((number-fromMin)/(fromHigh-fromMin))*(toHigh-toMin)+toMin);
}

function randomColor(){//Iestata random krasu
  if(turnOff==false){
    dataType = 1;
    for(var i = 0; i<4; i++){//sastada random krasas vertibas kuras saliek ieksa saraksta
      if(whiteAllowed == true && i == 3 || i<3){//izlaiž white vērtību, ja nebija nospiesta white poga
        rgbw[i] = Math.floor(Math.random()*255);
      }
    }
    stringColorSet();
  }
}

function ultraWhite(){//Iestata visas krasas uz maksimumu
  if(turnOff==false){
    rgbw = [255,255,255,255]; 
    dataType = 1;
    whiteAllowed = true;
    stringColorSet();
  }
}

function rainbowFunc(){
  if(turnOff==false){
    dataType = 2;
    funcNum = 1;
    sendValue(funcNumBuilder(funcNum));
  }
}

function fadeFunc(){
  if(turnOff==false){
    dataType = 2;
    funcNum =2;
    sendValue(funcNumBuilder(funcNum));
  }
}

function blinkFunc(){
  if(turnOff==false){
    dataType = 2;
    funcNum = 3;
    sendValue(funcNumBuilder(funcNum));
  }
}

function lmFunc(){
  if(turnOff==false){
    dataType = 3;
    sendValue();
  }
}

function funcNumBuilder(num){
  if(num>=100){
    return num;
  }else if(num>=10&&num<100){
    return "0" + num;
  }else{
    return "00" + num;
  }
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
    setButtonStyle[i-1].style.fontFamily = "Arial, Helvetica, sans-serif";
    setButtonStyle[i-1].style.fontSize = "16px";

    document.getElementById("lampButton"+i).addEventListener('click', function lampButton(){lampButtonClick(this);});//katrai no lampu pogām pievieno funkciju kura nosūta pašas pogas vērtību tālāk uz citu funkciju
  }
}

function lampButtonClick(buttonElement){//buttonElement ir veselas pogas vērtība
  if(turnOff==false){
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
      buttonElement.style.background = lampButtonDefault;//ja poga bija iepriekš nospiesta un tā tika nospiesta vēlreiz, tad mainās atpakaļ tās krāsa un tiek uzlikta nultā lampa
      buttonOn = false;
      lampNum = "00";
    } else if (buttonOn == false && oldLampNum == parseInt(lampNum)){//ja ir tā pati poga, bet tā iepriekš nebija ieslēgta
      buttonElement.style.background = lampButtonPressed;
      buttonOn = true;
    } else if (oldLampNum != parseInt(lampNum)){//ja tiek nospiesta poga, kura iepriekš nebija nospieta
      if(oldLampNum!=0){
        document.getElementsByClassName("lampButton")[oldLampNum-1].style.background = lampButtonDefault;
      }
      buttonElement.style.background = lampButtonPressed;
      buttonOn = true;
    }
  }
}

function sendValue(sendValueOutput){//parāda nosūtamos datus
  var sendPar = document.getElementById("outputText");//izvada vērtību uz ekrāna
  if(dataType == 1){//parasta krasas iestatisana
    sendPar.innerText = "<" + dataType + lampNum + sendValueOutput +">";
  }else if(dataType == 2){//funkciju nosutisana
    sendPar.innerText = "<" + dataType + "00" + sendValueOutput + "000" + ">";//pedejas tris nulles ir prieks parametru iestatisanas. pagaidam netiek izmantots
  }else if(dataType == 3){//gaismas muzikas nosutisana
    sendPar.innerText = "<3>";
  }else if(dataType == 0){//saskaitisanas nosutisana
    sendPar.innerText = "<000>";
  }
}

function valueState(valueStateOutput){//parāda vai dati tiek saņemti vai nosūtīti kā arī citus paziņojumus
  document.getElementById("outputState").innerText = valueStateOutput;
}

function setColor(){//izveido krāsu nosūtamo string vērtību
  if(turnOff==false){
    dataType = 1;
    var hexToRgb = document.getElementById("colorIn").value.match(/[A-Za-z0-9]{2}/g).map(function(v) { return parseInt(v, 16) }).join(",");//pārveido ievadītās krāsu vērtības no HEX uz RGB
    var colorNum = 0;//katru reizi mainās par 1 , lai ieliktu rgbw sarakstā 3 krāsu vērtības
    var colorCount = 0;//nepieciešams, lai izvietotu krāsu ciparu sarakstā vērtības
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
        for (var x = 0; x<3; x++){//saliek krāsu ciparus no saraksta vienā rindiņā izveidojot String skaitli
          countStr = countStr + colorChars[x].toString();
        }
        rgbw[colorCount] = parseInt(countStr);
        countStr = "";
        colorNum = 0;
        colorChars = [0, 0, 0];
        colorCount++;
      }
    }
    stringColorSet();
  }
}

function setBrightness(brightness){
  if(turnOff==false){
    if(dataType == 1){
      for(var i = 0; i<4; i++){
        rgbw[i] = Math.round(scaleToRange(brightness, 0, 100, 0, rgbw[i]));
      }
      stringColorSet();
    }
  }
}

function stringColorSet(){//Si funkcija parveido rgbw krasu vertibas String rindina. Gatavu izsutisanai
  var countString = "";
  for(var i=0; i<4; i++){//Nosaka vai saraksta skaitli ir divcipara vai viencipara vai trisciparu skaitlis un atbilstosi pieliek nulles
    if(rgbw[i]>=100){
      countString = rgbw[i];
    }else if (rgbw[i]<100 && rgbw[i]>=10){
      countString = "0" + rgbw[i];
    }else{ 
      countString = "00" + rgbw[i];
    }
    sendRGBString = sendRGBString + countString;
    countString = "";
  }
  sendValue(sendRGBString);
  sendRGBString = "";
}

//Paroles ievades dala
function submitPassword(){
  var password = "test";
  var passwordCheck = document.getElementById("passwordInput").value;
  if(passwordCheck == password){
    window.location.href = "main.html";
  }
}
//Paroles ievades dala beidzas

//Settings logs
document.getElementsByClassName("optionsDiv")[0].style.display = "none";
var openSettingsVar = false
function openSettings(){
  if(openSettingsVar == false){
    turnOff = false;
    openSettingsVar = true;
    document.getElementsByClassName("optionsDiv")[0].style.display = "block";
  } else {
    turnOff = true;
    openSettingsVar = false;
    document.getElementsByClassName("optionsDiv")[0].style.display = "none";
  }
}

function setNewPass(){

}

function lampCount(){

}

//lai darbotos ar datiem neizmantojot WiFi, ir jāizveido input lodzinš, kur tiks iekšā rakstītas vērtības

//Settingos var mainīt paroli
//Settingos atrodas lampu parskaitisanas

//izveidot lampu pārskaitīšanās nosūtīšanu

//izveidot funkciju, kas sadalītu lampu skaita vērtību no iekavām un izmantotu to turpmākajā skriptā

//<200[001]000> funkciju nosutisanas paraugs
//<000> lampu parskaitisanas nosutisanas paraugs
//<3> gaismas muzikas nosutisanas paraugs
//funkciju numuri nav zinami tapec tie tika izteikti sada veida: rainbow=1, fade=2, blink=3, onOff=0
//slideru vertibu parveidosana no 0-100 uz 0-255. Skaitliska veida tiks paradits viss procentos izmantojot map funkciju

//izveidot tā, lai funkcijas darbotos tikai tad, ja on off būls būtu true
//BOOKMARK1 ir iespeja pie ieslegsanas un izslegsanas noslept funkcionalo lapas dalu tadejadi tai lietotajam uz to bridi tai nebus piekluves. Sis ir atrais variants kuru butu velams uzlabot ar sarezgitaku un izskatigaku variantu

//Izveidot labu un parskatamu dizainu atbilstosi dazadiem ekranu izmeriem