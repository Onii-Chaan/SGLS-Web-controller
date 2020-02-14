class ColorBlock {
    constructor(colorName, colorValue, type, options = '') {
        this.colorName = colorName;//krāsas nosaukums
        this.colorValue = colorValue;//krāsas rgbw vērtība
        this.colorNameLen = this.colorName.length;//krāsas nosaukuma string garums
        this.colorBlock;//pats krāsas bloks
        this.colorBlockPar;//teksta atrašanās vieta
        this.type = type;//nosaka vai šī būs animācijas vai krāsu klase

        this.options = options; //animāciju un krāsu pogu editošanai

    }

    build() {//funkcija, kas atgriež gatavu krāsas bloku
        this.colorBlock = document.createElement('DIV');
        
        this.colorBlock.innerHTML = this.colorName;//izveido nosaukuma paragrāfu
        this.colorBlock.style.color = getContrast(this.colorValue.slice(0,3));//Maina teksta krāsu atbilstoši fona krāsai

        this.colorBlock.classList.add('ellipsisText');
        this.colorBlock.classList.add(this.type);
        this.colorBlock.style.background = 'rgba(' + this.colorValue[0] + ', ' + this.colorValue[1] + ', ' + this.colorValue[2] + ', ' + scaleToRange(this.colorValue[3] * 100, 0 * 100, 255 * 100, 1 * 100, 0.01 * 100) / 100 + ')';

        this.colorBlock.onclick = methodize(this.colClick, this);//pievieno notikumu un funkciju

        if (this.options != '') {
            this.colorBlock.ondblclick = methodize(this.dblclick, this);
        }
        return this.colorBlock;
    }

    colClick(){//krāsas klikšķis        
        if (this.type == 'animBlock'){
            sendValue(0, currentLampString, stringFunctionSet(this.colorValue[0], this.colorValue[1]));
            sendAjaxData('lamp='+'<1' + currentLampString + stringFunctionSet(this.colorValue[0], this.colorValue[1]) + '>' + ' ', 'setlamp');            
        }else{
            sendValue(1, currentLampString, stringColorSet(this.colorValue));
            sendAjaxData('lamp='+'<0' + currentLampString + stringColorSet(this.colorValue) + '>' + ' ', 'setlamp');
        }
    }

    dblclick() {
        this.dblData = [];//izveido atsevišķu masīvu nosūtīšanai uz funkciju
        this.dblData = [...this.colorValue]
        this.dblData[4] = this.colorName;
        this.options.open(this.dblData, this.colorBlock, this);
        console.log(this.colorValue);
    }

    grow(plusWidth = 0) {//izveido krāsu blokam atbilstošu platumu
        if (!plusWidth) {//strādā tikai tad, kad netiek likts papildus platums
            // console.log('TEST: ', this.colorBlock.clientWidth);
            this.colorBlock.style.width = this.colorBlock.clientWidth + Math.floor(this.colorBlock.clientWidth * 0.5) + 'px';//izveido atbilstošo bloka garumu
        } else if (plusWidth) {//ja ir papildus vērtība, ko pievienot
            this.colorBlock.style.width = this.colorBlock.clientWidth + plusWidth - 5 +'px';
        }
    }

    blockWidth() {//atgriež objekta platumu
        return this.colorBlock.clientWidth + 5/*margin-left*/;
    }

    updateData(name = '', value = ''){
        if(name != this.colorName && name != '' && typeof name != 'undefined'){//pārbauda vai var apdeitot nosaukumu
            this.colorBlock.innerHTML = name;
            this.colorName = name;
            // this.colorValue[4] = name;
        }
        if(value != this.colorValue[1] && value != '' && typeof value != 'undefined'){
            this.colorBlock.setAttribute('name', this.colorValue[0] + '|' + value) ;
        }
    }
    
    show(){//parāda HTML elementu
        return this.colorBlock;
    }

    getData(){
        return [this.colorName, this.colorValue];
    }
}



