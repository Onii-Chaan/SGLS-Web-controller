class SettingsPopUp {//pop elementu klase
    constructor(title, inputFields, buttonCount, index, type) {
        this.title = title;//popapa virsraksts
        this.inputFields = inputFields;//visu ievades lauciņu raksturojumi
        this.buttonCount = buttonCount;//Pogu daudzums

        this.popUp;//PopUp elementa galvenais div
        this.data;//saglabā lietotāja ievadītos input datus

        this.index = index;//nepieciešams, lai saglabātu vai dzēstu informāciju EEPROMā
        this.type = type;//nosaka vai šī ir grupas, animācijas, vai krāsu poga
    }

    build() {
        this.popUp = buildElementNode('DIV', 'settingsPopUp');//izveido pop up divu
        this.popElement = buildElementNode('FORM', 'popUpForm');
        this.popUp.appendChild(buildElementNode('H3', 'settingsPopTitle', this.title));//izveido virsrakstu

        var inputCount = this.inputFields.length;
        for (i = 0; i < inputCount; i++) {//izveido visus ievades lauciņus
            if (this.inputFields[i][1] != 'double') {
                this.popElement.appendChild(buildElementNode('P', '', this.inputFields[i][0]));
                this.createInput = buildElementNode('INPUT', this.inputFields[i][1]);
                this.createInput.classList.add('popUpInput');
                this.popElement.appendChild(this.createInput);
            } else {
                this.popElement.appendChild(buildElementNode('P', '', this.inputFields[i][0]));
            }
        }
        this.buttonHolder = buildElementNode('DIV', 'actionButtonsHolder');//izveido pogas divu
        if (this.buttonCount == 2) {
            this.buttonHolder.appendChild(buildElementNode('BUTTON', 'actionButton', 'Save'));
            this.buttonHolder.appendChild(buildElementNode('BUTTON', 'actionButton', 'Close'));
        } else {//ja ir visas 3 pogas
            this.buttonHolder.appendChild(buildElementNode('BUTTON', 'actionButton', 'Save'));
            this.buttonHolder.appendChild(buildElementNode('BUTTON', 'actionButton', 'Delete'));
            this.buttonHolder.appendChild(buildElementNode('BUTTON', 'actionButton', 'Close'));
        }

        this.popUp.appendChild(this.popElement);
        this.popUp.appendChild(this.buttonHolder);//pievieno pogas galvenajam divam
        this.popElement = document.body.appendChild(this.popUp);//pop up element, lai ar to varētu turpāk veikt manipulācijas


        if (this.buttonCount == 3) {
            this.popElement.getElementsByClassName('actionButton')[0].addEventListener('click', this.save);
            this.popElement.getElementsByClassName('actionButton')[1].addEventListener('click', this.delete);
            this.popElement.getElementsByClassName('actionButton')[2].addEventListener('click', this.close);
        } else {
            this.popElement.getElementsByClassName('actionButton')[0].addEventListener('click', this.save);
            this.popElement.getElementsByClassName('actionButton')[1].addEventListener('click', this.close);
        }
        backShadow(false);//iestata fona ēnu

    }

    setCover(set) {//lapas fons, kad tiek atvērts kāds no settingiem
        if (set) {
            this.cover.style.display = 'block';
        } else {
            this.cover.style.display = 'none';
        }
    }

    open() {//parāda settings logu
        this.setCover(true);
        this.popUp.style.display = 'block';
    }

    save() {//nosūta uz serveri lietotāja jaunos ievadītos datus
        this.formCount = document.getElementsByClassName('popUpInput').length;
        this.inputElem = document.getElementsByClassName('popUpInput');
        
        this.saveName = 'name=' + this.inputElem[0].value;//nolasa input datus un atbilstoši tos pārveido
        if(this.formCount<3){
            this.saveValue = 'value='+this.inputElem[1].value;
        }else if(this.formCount == 3){
            this.saveValue = 'value='+createGroupString(this.inputElem[1].value, this.inputElem[2].value);
        }
        
        ajaxConsoleSend(this.saveName + ' ' + this.saveValue);
        document.getElementsByClassName('popUpForm')[0].reset();
        console.log('save');
    }

    close() {//noslēpj settings logu
        backShadow(false);//iestata fona ēnu
        document.getElementsByClassName('settingsPopUp')[0].style.display = 'none';
        console.log(document.getElementsByClassName('settingsPopUp'));
        console.log('close');
    }

    delete() {//izdzēš atbilstošo vērtību
        console.log('delete');
        backShadow(false);//iestata fona ēnu
        document.getElementsByClassName('settingsPopUp')[0].style.display = 'none';
    }

    returnData(dataToGet) {
        return;
    }

    updateIndex(newIndex) {
        this.index = newIndex;
    }
}