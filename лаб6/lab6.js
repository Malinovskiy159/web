const left_btn = document.getElementById('left_photo')

left_btn.addEventListener('click', () => {
	const cats = document.querySelector('.cat')
	cats.style.width = '560px'
	const dogs = document.querySelector('.dog')
	dogs.style.width = '40px'
	let image1 = document.querySelector('.img1')
	image1.style.width = '510px'
	let image2 = document.querySelector('.img2')
	image2.style.width = '0px'
})

const right_btn = document.getElementById('right_photo')

right_btn.addEventListener('click', () => {
	const cats = document.querySelector('.cat')
	cats.style.width = '40px'
	const dogs = document.querySelector('.dog')
	dogs.style.width = '560px'
	let image1 = document.querySelector('.img1')
	image11.style.width = '0px'
	let image2 = document.querySelector('.img2')
	image2.style.width = '510px'
})

const middle_btn = document.getElementById('both_photo')

middle_btn.addEventListener('click', () => {
	const cats = document.querySelector('.cat')
	cats.style.width = '300px'
	const dogs = document.querySelector('.dog')
	dogs.style.width = '300px'
	let image1 = document.querySelector('.img1')
	image1.style.width = '270px'
	let image2 = document.querySelector('.img2')
	image2.style.width = '270px'
})