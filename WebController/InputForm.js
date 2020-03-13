class InputForm {
    constructor(titleText, inputArr, placeToBuild) {
        this.titleText = titleText;//Paskaidrojošais teksts
        this.inputArr = inputArr;//Ievadlodziņi, to paskaidrojošie teksti
        this.placeToBuild = placeToBuild;//vieta, kur tiks ieveidots input logs

        this.formElement;//Definē formas elementu, lai to varētu izmantot visā klasē
        this.sendBuffer;//Lai saglabātu tekstu visā klasē, ko nosūtīt uz ajax
    }

    build(buttText, inputTypes = '', buttonDataSend = '') {
        this.sendBuffer = buttonDataSend;
        this.buttText = buttText;//Pogas teksts
        this.inputTypes = inputTypes;//masīvs, kurā atrodas array elementu veidi

        this.formDiv = buildElementNode('DIV', 'formDiv');//izveido pop up divu
        this.formElement = buildElementNode('FORM', 'formElement');
        this.formDiv.appendChild(buildElementNode('H3', 'formTitle', this.titleText));//izveido virsrakstu

        this.inputCount = this.inputArr.length;
        for (var i = 0; i < this.inputCount; i++) {//izveido visus ievades lauciņus
            this.formElement.appendChild(buildElementNode('P', '', this.inputArr[i]));//Input logu paskaidrojošais teksts            
            this.inputElement = buildElementNode('INPUT');//Iveido input elementu
            this.inputElement.setAttribute('name', this.inputTypes[i]);
            if (this.inputTypes[i] == 'ssid') {//Izveido ievades lauciņu atbilstošos tipus
                this.inputElement.setAttribute('type', 'text');
            } else if (this.inputTypes[i] == 'pass') {
                this.inputElement.setAttribute('type', 'password');
            }
            this.formElement.appendChild(this.inputElement);//pievieno input elementu formai
        }
        this.submitButton = buildElementNode('BUTTON', 'submitButton');//izveido pogas divu
        this.submitButton.innerHTML = this.buttText;
        if (this.inputCount > 0) {
            this.submitButton.onclick = methodize(this.checkData, this);
        } else {
            this.submitButton.onclick = methodize(this.buttonSend, this)
        }

        this.formDiv.appendChild(this.formElement);
        this.formDiv.appendChild(this.submitButton);
        this.placeToBuild.appendChild(this.formDiv);//Pievieno formu ievadītajai lokācijai
    }

    checkData() {
        checkForm(this.formElement);
    }

    buttonSend() {
        ajaxConsoleSend(this.sendBuffer);
    }
}