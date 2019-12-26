class CollapsibleButton {//izbīdamo pogu klase
    constructor(iconObj, textToAppend, elementHolder, secIcon = '', collContId = '') {

        this.iconObj = iconObj;//ikonas objekts, kas tiks parādīts pogas sānā
        this.textToAppend = textToAppend;//Teksts, kas parādīsies uz pogas
        this.elementHolder = elementHolder;//Elements, kurā atradīsies poga



        this.collButton;//galvenā poga, kas tiek izveidota
        this.labelDiv;
        this.smHolder;

        this.objectHolder;

        this.secIcon = secIcon;//Papildus ikona, ja ir nepieciešamība
        
        this.collContId = collContId;//Dotā collapsible kontenta ID
    }


    buildCollapseButton() {//Izveido pogas elementu un tajā esošo kontentu
        this.objectHolder = document.createElement('DIV');
        //this.objectHolder.style.marginBottom = '20px';
        this.labelDiv = document.createElement('P');

        this.collButton = document.createElement('BUTTON');//izveido pogas elementu, kas arī būs pati poga
        this.collButton.style.height = '30px';


        this.collButton.classList.add('collapsibleObj');
        this.collButton.classList.add('collapsible');//pievieno klasi pogai
        this.collButton.classList.add('expandButton');//pievieno klasi pogai

        if (this.secIcon != '') {//pievieno otro ikonu
            this.collButton.appendChild(this.secIcon.buildArrow());
        }

        var textToAdd = document.createTextNode(this.textToAppend);//Izveido tekstu pogai
        this.labelDiv.classList.add("collapsibleLabel");
        this.labelDiv.appendChild(textToAdd);//pievieno tekstu pogai
        this.collButton.appendChild(this.labelDiv);//pievieno tekstu pogai


        this.collButton.appendChild(this.iconObj.buildArrow());//ikona tiek pievienota pogas objektam


        this.smHolder = document.createElement("DIV");
        this.smHolder.classList.add('elemPlaceHolder');
        this.smHolder.classList.add('content');
        //textToAdd = document.createTextNode(this.textToAppend);//Izveido tekstu pogai
        //this.smHolder.appendChild(textToAdd);/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        if(this.collContId != ''){//iestata kontenta ID, lai to varētu izmantot ievietojot tajā elementus
            this.smHolder.id = this.collContId;
        }

        this.objectHolder.appendChild(this.collButton);//pievieno izveidoto pogu un tās elementus elementam, kur atrodas poga
        this.objectHolder.appendChild(this.smHolder);

        this.elementHolder.appendChild(this.objectHolder);
    }

    updateContent(contentToAdd){//apdeito kontentu
        if(this.collContId != ''){
            document.getElementById(this.collContId).appendChild(contentToAdd);
        } 
    }

    contentLength(){//iegūst kontenta elementa platumu
        return document.getElementById(this.collContId).clientWidth;
    }
}



