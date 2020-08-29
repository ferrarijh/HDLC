# HDLC
Simluate stop-and-wait protocol at data-link layer. Output simulation result(ack, seq, success, failure, etc..) on timeline.
Details are at 'problem statement.txt'

## Demo
On startup, the program prompts to input 3 values - simulation time, loss probability and corruption probability. In this demo each are set to 2000, 0.2, 0.2 respectively.
When frame is corrupted, receiver sends back NAK to sender and termial outputs <b>"Corrupted frame. Receiver sends NAK."</b>. When frame is loss receiver's timeout(15ms) is triggered and terminal outputs <b>"Receiver timeout."</b>

<div>
  <img src="https://github.com/ferrarijh/HDLC/blob/master/demo/1.png">
</div>
This is what you'll see immediately.
<br></br>
<div>
  <img src="https://github.com/ferrarijh/HDLC/blob/master/demo/2.png">
</div>
ACK and SEQ alternates between successfully sent frames.
<br></br>
<div>
  <img src="https://github.com/ferrarijh/HDLC/blob/master/demo/3.png">
</div>
Frames are resent when arrivd frame is corrupted.
<br></br>
<div>
  <img src="https://github.com/ferrarijh/HDLC/blob/master/demo/4.png">
</div>
Maximum number of attempts to send frame is set to <i>N_r</i> = 3. After 3 trials the frame is dropped and next queued frame will be sent.
<br></br>
<div>
  <img src="https://github.com/ferrarijh/HDLC/blob/master/demo/5.png">
</div>
Final result is shown at the bottom.
