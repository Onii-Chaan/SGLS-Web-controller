//TE ATRODAS VISI GLOBĀLIE MAINĪGIE UN TO PASKAIDROJUMI

//var totalLamps = Number(prompt("Ievadi lampu daudzumu: "));
var lampButtonPressed = "#9ab8a0";//dinamisko pogu krasa kad ta tika nospiesta
var lampButtonDefault = "#6c8270";//dinamisko pogu krasa kad ta nav nospiesta

var dataType;//izsūtāmo vērtību tips, vai tā ir saskaitīšanās, funkcija vai krāsa
var buttonOn = false;//norada vai lietotajs darbojas ap vienu lampu vai ap visam kopa, tiek izmantots, lai nevaretu ieslegt funkcijas kad darbojas ap vienu lampu
var lampNum = "00";//lampu numura String vērtība
var whiteAllowed = false;//atļauj vai arī aizliedz izmantot balto krāsu funkcijās
var funcNum = 0;//lampu funkcijas numurs
var currentLamp; //seko līdzi tam, kura lampa ir pašlaik nospiesta
//document.getElementsByClassName("hidable")[0].style.display = "none"; BOOKMARK1

var lampGroups = [['Room1', '1-5#'], ['BedRoom', '2-8#'], ['Garden', '6-7#']];//ienākošo lampu grupu datu masīvs