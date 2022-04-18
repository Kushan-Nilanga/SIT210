from guizero import App, ButtonGroup, PushButton
import RPi.GPIO as GPIO


iobuttons = [['Red 1', 36], ['Red 2', 38], ['Red 3',40]]

def change_io():
	pin = int(bg.value)
	
	for x in iobuttons:
		GPIO.output(x[1], GPIO.LOW)
	
	GPIO.output(pin, GPIO.HIGH)
	
def close_app():
	GPIO.cleanup()
	exit(0)
	
if __name__=='__main__':
	GPIO.setmode(GPIO.BOARD)
	for x in iobuttons:
		GPIO.setup(x[1], GPIO.OUT)

	app = App(title='Simple GUI', height=100)
	bg = ButtonGroup(app, options=iobuttons, horizontal=True, command=change_io)
	PushButton(app, text='Exit', command=close_app)
	app.display()
