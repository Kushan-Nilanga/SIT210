import RPi.GPIO as GPIO
import time


try:
    # max value to be calibrated
    max_dist = None

    TRIG = 38  # ultrasound sensor trig pin
    ECHO = 40  # ultrasound sensor echo pin
    PWML = 32  # LED PWM pin

    GPIO.setmode(GPIO.BOARD)    # set board pin names
    GPIO.setup(TRIG, GPIO.OUT)  # setup trig pin output
    GPIO.setup(ECHO, GPIO.IN)   # setup echo pin input
    GPIO.setup(PWML, GPIO.OUT)  # setting PWM pin for LED
    pwml = GPIO.PWM(PWML, 100)  # setting PWM frequency
    pwml.start(0)               # starting PWM communication

    GPIO.output(TRIG, GPIO.LOW)
    time.sleep(2)               # sleep for 2 seconds

    while True:
        # getting distance
        GPIO.output(TRIG, GPIO.HIGH)
        time.sleep(0.00001)
        GPIO.output(TRIG, GPIO.LOW)

        while GPIO.input(ECHO) == 0:
            pulse_start = time.time()

        while GPIO.input(ECHO) == 1:
            pulse_end = time.time()

        pulse_duration = pulse_end - pulse_start

        # distance in centimeters
        distance = pulse_duration * 17150

        # calibrating the max distance if not configured
        if max_dist is None:
            max_dist = distance

        # setting duty cycle w.r.t distance
        duty_time = (100.0 / max_dist) * distance
        # clipping duty time between 0 and 100
        duty_time = max(min(duty_time, 100.0), 0.1)
        brightness = 100.0 - duty_time
        print(brightness)
        pwml.ChangeDutyCycle(brightness)  # changing duty cycle
        time.sleep(0.1)


except KeyboardInterrupt:
    pwml.stop()
    GPIO.cleanup()
