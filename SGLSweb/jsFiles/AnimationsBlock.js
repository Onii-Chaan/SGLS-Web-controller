class AnimationsBlock extends ColorBlock{//animāciju bloks ir tāds pats kā ColorBlock, bet ar citiem parametriem
    buildAnimBlock(){
        this.colorBlock = document.createElement('DIV');

        this.colorBlock.innerHTML += this.colorName;//izveido nosaukuma paragrāfu

        this.colorBlock.classList.add('animBlock');

        this.colorBlock.setAttribute('name', this.colorValue[0] + '|' + this.colorValue[1]);//lai varētu vēlāk iegūt funkciju vērtības no elementa name
     
        this.colorBlock.addEventListener('click', function () {
            var findMatch = this.getAttribute('name').match(/\d+/g);//atrod iekš name esošos parametrus funkcijai
            sendValue(1, '1-42', stringFunctionSet(findMatch[0], findMatch[1]));
        });
        return this.colorBlock;
    }
}
