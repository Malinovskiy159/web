class Items {
	constructor() {
		this.items = new Set()
	}

	render() {
		const items = document.getElementById('items')
		items.innerHTML = ''

		this.items.forEach(({ key, value, id }) => {
			const item = document.createElement('div')
			item.setAttribute('key', id)

			const key_input = document.createElement('input')
			key_input.setAttribute('name', id)
			key_input.value = key
			key_input.addEventListener('change', e => {
				this.editItem(e.target.name, e.target.value)
				console.log(this.items)
			})

			const value_input = document.createElement('input')
			value_input.setAttribute('name', id)
			value_input.value = value
			value_input.addEventListener('change', e => {
				this.editItem(e.target.name, undefined, e.target.value)
				console.log(this.items)
			})

			const move_down_button = document.createElement('button')
			move_down_button.innerHTML = '&darr;'
			move_down_button.addEventListener('click', () => this.moveDown(id))

			const move_up_button = document.createElement('button')
			move_up_button.innerHTML = '&uarr;'
			move_up_button.addEventListener('click', () => this.moveUp(id))

			const delete_button = document.createElement('button')
			delete_button.innerHTML = '&#215;'
			delete_button.addEventListener('click', () => this.deleteItem(id))

			item.append(key_input, value_input, move_up_button, move_down_button, delete_button)
			items.appendChild(item)
		})
	}

	moveUp(item_id) {
		const items = Array.from(this.items)

		for (const [index, { id }] of items.entries()) {
			if (id == item_id) {
				if (index === 0) continue
				;[items[index], items[index - 1]] = [items[index - 1], items[index]]
				break
			}
		}

		this.items = new Set(items)
		this.render()
	}

	moveDown(item_id) {
		const items = Array.from(this.items)

		for (const [index, { id }] of items.entries()) {
			if (id == item_id) {
				if (index === this.items.size - 1) continue
				;[items[index], items[index + 1]] = [items[index + 1], items[index]]
				break
			}
		}

		this.items = new Set(items)
		this.render()
	}

	addItem() {
		this.items.add({ key: '', value: '', id: this.items.size })
		this.render()
	}

	editItem(item_id, key = undefined, value = undefined) {
		for (const item of this.items) {
			if (item.id == item_id) {
				if (key) {
					item.key = key
				}
				if (value) {
					item.value = value
				}
			}
		}
	}

	deleteItem(id) {
		this.items.forEach(item => {
			if (item.id == id) {
				this.items.delete(item)
			}
		})

		this.render()
	}

	getItems() {
		return this.items
	}

	printItems() {
		const result = document.getElementById('result')
		result.innerHTML = ''

		const items = Array.from(this.items).map(item => {
			return { [item.key]: item.value }
		})
		const items_string = JSON.stringify(items)
		const items_node = document.createTextNode(items_string.substring(1, items_string.length - 1))
		result.appendChild(items_node)
	}
}

function saveItem() {
	document.getElementById('#save-item')
}

function main() {
	const items = new Items()

	const saveButton = document.getElementById('save-item')
	saveButton.addEventListener('click', () => items.printItems())

	const addButton = document.getElementById('add-item')
	addButton.addEventListener('click', () => items.addItem())
}

main()