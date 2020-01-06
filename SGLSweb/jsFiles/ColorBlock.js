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

        this.colorBlock.classList.add(this.type);
        this.colorBlock.style.background = 'rgba(' + this.colorValue[0] + ', ' + this.colorValue[1] + ', ' + this.colorValue[2] + ', ' + scaleToRange(this.colorValue[3] * 100, 0 * 100, 255 * 100, 1 * 100, 0.01 * 100) / 100 + ')';

        this.colorBlock.addEventListener('click', function () {
            sendValue(0, '1-17', stringColorSet(parseToRGBA(this.style.backgroundColor)));
        });

        if (this.options != '') {
            this.colorBlock.ondblclick = methodize(this.dblclick, this);
        }
        return this.colorBlock;
    }

    dblclick() {
        this.dblData = this.colorValue;//izveido atsevišķu masīvu datu nosūtīšanai
        this.dblData.push(this.colorName);
        this.options.open(this.dblData, this.colorBlock, this);
    }

    grow(plusWidth = 0) {//izveido krāsu blokam atbilstošu platumu
        if (!plusWidth) {//strādā tikai tad, kad netiek likts papildus platums
            this.colorBlock.style.width = this.colorBlock.clientWidth + this.colorBlock.clientWidth * 0.5 + 'px';//izveido atbilstošo bloka garumu
        }

        if (plusWidth) {//ja ir papildus vērtība, ko pievienot
            this.colorBlock.style.width = this.colorBlock.clientWidth + plusWidth + 'px';
        }
    }

    blockWidth() {//atgriež objekta platumu
        return this.colorBlock.clientWidth + 5/*margin-left*/;
    }

    updateData(name = '', value = ''){
        if(name != this.colorName && name != '' && typeof name != 'undefined'){//pārbauda vai var apdeitot nosaukumu
            this.colorBlock.innerHTML = name;
        }
        console.log('befvalue: ', value);

        if(value != this.colorValue[1] && value != '' && typeof value != 'undefined' ){
            console.log('value: ', value);
            console.log('name', this.colorValue[0] + '|' + value);
            this.colorBlock.setAttribute('name', this.colorValue[0] + '|' + value) ;
        }
    }
}



