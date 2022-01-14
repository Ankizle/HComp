package main

import (
	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/app"
	"fyne.io/fyne/v2/container"
	"fyne.io/fyne/v2/widget"
)

var derr = "DETATCH ERROR:"
var segf = "SEGFAULT"

func main() {
	bapp := app.New()
	window := bapp.NewWindow("HComp")

	// Main menu
	fileMenu := fyne.NewMenu("File",
		fyne.NewMenuItem("Download Executable", func() {
			//TODO
		}),
		fyne.NewMenuItem("Quit", func() { bapp.Quit() }),
	)

	mainMenu := fyne.NewMainMenu(
		fileMenu,
	)
	window.SetMainMenu(mainMenu)

	searchbar := widget.NewEntry()
	searchbar.SetPlaceHolder("Enter URI of the HComp site")
	searchbar.OnSubmitted = func(uri string) {

	}

	box := container.NewVBox(
		searchbar,
	)

	window.SetContent(box)
	window.Resize(fyne.NewSize(500, 500))

	window.ShowAndRun()
}
