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

static const char index_html[] PROGMEM = (R"EOF(
<!DOCTYPE html>
<html>

<head>
<title>Safe</title>
<link rel="shortcut icon" href="data:image/x-icon;base64,AAABAAEAEA4AAAEAIADgAwAAFgAAACgAAAAQAAAAHAAAAAEAIAAAAAAAgAMAAMMOAADDDgAAAAAAAAAAAAD+/v7///////j4+P/29vb///////////////////////////////////////7+/v/19fX/+/v7///////9/f3//////6Kiov9ISEj/T09P/4mJif+Ghob/hoaG/4WFhf+Ghob/hoaG/4eHh/+CgoL/RERE/1VVVf++vr7//////8rKyv9ycnL/2dnZ/6qqqv+np6f/pqam/6SkpP+pqan/qKio/6SkpP+mpqb/p6en/7Kysv/R0dH/aGho//Hx8f+9vb3/mZmZ/4CAgP9zc3P/jo6O/4+Pj/+ampr/gICA/4WFhf+bm5v/ioqK/5OTk/9hYWH/nJyc/4mJif/l5eX/v7+//5SUlP+Ghob/5eXl///////y8vL/jIyM/3Fxcf9xcXH/oaGh//7+/v//////wMDA/5KSkv+IiIj/5eXl/76+vv+UlJT/h4eH/+Pj4///////Tk5O/6Kiov/a2tr/5ubm/3Jycv93d3f//////7q6uv+UlJT/iIiI/+Xl5f++vr7/l5eX/3p6ev/l5eX/wMDA/4+Pj//R0dH/Y2Nj/2pqav/m5ub/cHBw//Hx8f/Gxsb/kpKS/4iIiP/l5eX/vb29/56env9XV1f/paWl/6+vr/+goKD/iYmJ/9fX1/+lpaX/rKys/319ff/a2tr/y8vL/5KSkv+IiIj/5eXl/76+vv+VlZX/gYGB/+7u7v/Ly8v/gICA/+Li4v9jY2P/d3d3/+rq6v9oaGj/+vr6/8TExP+Tk5P/iIiI/+Xl5f++vr7/lZWV/4eHh//i4uL//////2JiYv+BgYH/3Nzc/97e3v9XV1f/j4+P//////+8vLz/lJSU/4iIiP/l5eX/v7+//5OTk/+FhYX/5eXl///////9/f3/oqKi/2ZmZv9ra2v/ubm5////////////wMDA/5GRkf+IiIj/5eXl/729vf+YmJj/kpKS/21tbf+Dg4P/f39//5CQkP+Kior/jIyM/46Ojv99fX3/hoaG/2JiYv+srKz/hYWF/+Xl5f/U1NT/aGho/8HBwf+lpaX/p6en/6ampv+kpKT/paWl/6SkpP+kpKT/p6en/6ampv+rq6v/tra2/2dnZ//39/f//////7S0tP9/f3//jY2N/4uLi/+Li4v/i4uL/4uLi/+Li4v/i4uL/4uLi/+Li4v/jIyM/39/f//Nzc3//////wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" />
</head>

<frameset rows = "8%,*">
  <frame name = "top" src = "top_frame.html" />

  <frameset cols = "30%,70%">
    <frame name = "menu" src = "menu_frame.html" />
    <frame name = "main" src = "safe/?status=1" />
  </frameset>

  <noframes>
     <body>Your browser does not support frames.</body>
  </noframes>

</frameset>

</html>
)EOF");

static const char main_frame_html[] PROGMEM = (R"EOF(
main
)EOF");

static const char menu_frame_html[] PROGMEM = (R"EOF(
<html>
<head>
  <base target="main">
  <title>Safe menu</title>
</head>
<body>
<center><h2>Menu</h2>
<p>
<form method=post action=safe/ enctype="multipart/form-data">
<input type=submit value=Status name=status>
</form>
<hr>
<form method=post action=safe/ enctype="multipart/form-data">
Open safe door:<br>
<select name="duration">
  <option value="5">5 seconds</option>
  <option value="10">10 seconds</option>
  <option value="20">20 seconds</option>
  <option value="30">30 seconds</option>
  <option value="60">60 seconds</option>
</select>&nbsp;&nbsp;
<input type=submit value="Open Safe" name=open>
</form>
<hr>
<form method=post action=safe/ enctype="multipart/form-data">
Set Lock Session<br>
This is the lock ID value:<br>
<input type=input name=session length=40><br>
<input type=submit value="Set Lock" name=set_lock>
</form>
(See documentation on how to find this)
<hr>
<a href="change_auth.html">Change Safe Chaster Details</a>
<br>
<hr>
<a href="change_ap.html">Change Safe Connection Details</a>
<br>
<hr>
<a href="enable_update">Enable Safe Network Update</a>
<br>
<a href="disable_update">Disable Safe Network Update</a>
<br>
<hr>
</center>
</form>
</body>
</html>
)EOF");

static const char top_frame_html[] PROGMEM = (R"EOF(
<html>
<body>
<center><h1>Chaster safe controls</h1></center>
</body>
</html>
)EOF");

