static const char change_ap_html[] PROGMEM = (R"EOF(
<html>
<body>

<form method=post enctype="multipart/form-data">
To set the WiFi network details, enter here:
<br>
WiFi SSID: <input name=ssid size=40>
<br>
WiFi Password: <input name=password size=40>
<br>
Safe name: <input name=safename size=40 value="##safename##">
<br>
GPIO pin to trigger solenoid (default 12): <input name=pin size=2 value="##pin##">
<br>
For reference these are the pins on a NodeMCU 12E board:
<blockquote>
<pre>
GPIO16 == D0
GPIO5  == D1
GPIO4  == D2 (pin on ESP8266/Relay board)
GPIO0  == D3
GPIO2  == D4
GPIO14 == D5
GPIO12 == D6 (the default)
GPIO13 == D7
GPIO15 == D8
</pre>
</blockquote>
<br>
<input type=submit value="Set WiFi" name=setwifi>
<hr>
If the change is accepted, the safe will reboot after 5 seconds.
<hr>
<p>
&nbsp;
<p>
&nbsp;
<font size=-3>Software version: ##VERSION##</font>
</form>
</body>
</html>
)EOF");

static const char change_auth_html[] PROGMEM = (R"EOF(
<html>
<body>
<form method=post action=safe/ enctype="multipart/form-data">
To set the user name and password needed to access the safe:
<br>
Safe Username: <input name=username size=40 value="##ui_username##">
<br>
Safe Password: <input name=password size=40>  (keep blank to leave unchanged)
<p>
<input type=submit value="Set Auth Details" name=setauth>
<p>
If the change is accepted, you will need to login again.
<hr>
To talk to the Chaster Server you need to enter your API Developer token
details.  See the README on how to find this
<br>
Developer token: <input name=token size=40 value="##token##">
<p>
<input type=submit value="Set API Details" name=setapi>
<p>
If the values are incorrect you will not be able to talk to the server
and will need to correct the values.
<p>
The default endpoint this software talks to is the Chaster API.
This may be changed here (if no lock is running) to another endpoint
that supports the <tt>checklock.php</tt> endpoint.  NOTE: the server
must also use the same CA so we can do secure communication.
<p>
<input name=apiurl size=50 value="##apiurl##">
<p>
<input type=submit value="Change API URL" name=setapiurl>
</form>
</body>
</html>
)EOF");

