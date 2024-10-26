const popUp = document.getElementById('pop_up');
const popUp2 = document.getElementById('pop_up2');
const popUp3 = document.getElementById('pop_up3');

const openPopUp1 = document.getElementById('open_pop_up1');
const closePopUp1 = document.getElementById('pop_up_close1');

const openPopUp2 = document.getElementById('open_pop_up2');
const closePopUp2 = document.getElementById('pop_up_close2');

const openPopUp3 = document.getElementById('open_pop_up3');
const closePopUp3 = document.getElementById('pop_up_close3');

openPopUp1.addEventListener('click', function(e){
    e.preventDefault();
    popUp.classList.add('active');
})

closePopUp1.addEventListener('click', function(){
    popUp.classList.remove('active');
})

openPopUp2.addEventListener('click', function(e){
    e.preventDefault();
    popUp2.classList.add('active');
})

closePopUp2.addEventListener('click', function(){
    popUp2.classList.remove('active');
})

openPopUp3.addEventListener('click', function(e){
    e.preventDefault();
    popUp3.classList.add('active');
})

closePopUp3.addEventListener('click', function(){
    popUp3.classList.remove('active');
})

block1.onmouseover = function (){
    block1.style.background = "#d34949";
};

block1.onmouseleave = function () {
    block1.style.background = "aquamarine";
};

block2.onmouseover = function (){
    block2.style.background = "#d34949";
};

block2.onmouseleave = function () {
    block2.style.background = "aquamarine";
};

block3.onmouseover = function (){
    block3.style.background = "#d34949";
};

block3.onmouseleave = function () {
    block3.style.background = "aquamarine";
};