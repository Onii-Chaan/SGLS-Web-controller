class InputForm{
    constructor(titleText, inputArr, placeToBuild){
        this.titleText = titleText;//Paskaidrojošais teksts
        this.inputArr = inputArr;//Ievadlodziņi, to paskaidrojošie teksti
        this.placeToBuild = placeToBuild;//vieta, kur tiks ieveidots input logs
    }

    build(){
        this.formDiv = buildElementNode('DIV', 'formDiv');//izveido pop up divu
        this.formElement = buildElementNode('FORM', 'formElement');
        this.formDiv.appendChild(buildElementNode('H3', 'formTitle', this.titleText));//izveido virsrakstu

        this.inputCount = this.inputArr.length;
        for (var i = 0; i < this.inputCount; i++) {//izveido visus ievades lauciņus
            this.formElement.appendChild(buildElementNode('P', '', this.inputArr[i]));//Input logu paskaidrojošais teksts
            this.formElement.appendChild(buildElementNode('INPUT'));
        }
        this.submitButton = buildElementNode('BUTTON', 'submitButton');//izveido pogas divu
        this.formElement.appendChild(this.submitButton);
        
        this.formDiv.appendChild(this.formElement);
        this.placeToBuild.appendChild(this.formDiv);//Pievieno formu ievadītajai lokācijai
    }
}