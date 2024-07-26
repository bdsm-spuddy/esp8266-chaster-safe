## Chaster Safe software

This is a version of the software for my digital safe ([v2](https://bdsm.spuddy.org/writings/Safe_v2/) and [v3](https://bdsm.spuddy.org/writings/Safe_v3/))
designed to work uniquely with [Chaster](https://chaster.app)

Follow the instructions on that page to build the hardware, but the software
here can be uploaded to the ESP8266 board instead.  Do read the software
instructions on that page, though, to understand how to do initial setup,
configuring for WiFi, etc.

Instead of entering a combination, you can enter a lockID value
instead.

### Diffences between the normal software.

On the original software you just needed to enter a username/password
to protect the safe from having an outsider change things.

In this version there is one more things to configure:

* Developer token

This uses the Chaster API.  You first need to register for a developer
account (see [the docs](https://chaster.app/developers)).

Once you have been approved (which should take minutes if you use the
same email address as your Chaster account) then you can create an
application in the [developer interface](https://chaster.app/developers/applications).
You can call this whatever you like; I used "read lock status".  You don't
need any URIs because we're not using OAuth.

Once the application has been created, you should be taken to a screen
where you can manage that app.  On the left menu you'll see a tab called
"tokens".  Click on that and then "Generate a developer token".  This
will generate a token, and it's this value you will need to enter into
the safe.  

This token lets you see and manage your locks (eg add time, create a lock).
This code just reads a lock details.

### Typical usage

* Setup the username/password and developer token.

You can test this all works by then tryin a dummy lock; enter `123` as
the lock ID.  If it all works then you should get the response
`Problems talking to API: Response 404`.  Otherwise
you'll get an error explaining what is wrong

Typical errors:

* 401: The developer token is wrong
* 404: The lockID is wrong.
* -1: Connectivity to the API isn't working.  This is where it gets
complicated because there could be many reasons.  One cause could be
it literally can not reach the API server; there's a connectivity
problem.  More common is that the TLS certificate failed to validate
properly.  This code expects the certificate to be signed by the 
Google Trust Services "GTS Root 4".  If this changes then the safe
will break!!

* Create the lock in the chaster web site

Create the lock as normal.  Do whatever you want (eg load a shared lock
or generate a self-lock).  The combination doesn't matter so you might as
well select "generated combination"

*NOTE* Not all key holders like generated combinations; they think it
allows people to cheat easier.  You might want to discuss this before
loading the lock.  This safe is more secure than any keybox or combination
lock!

Now we need to get the lock ID.  The easiest way is on the "Locks" page;
select your lock and then select the "Settings" tab.  The page URL will
look something like `https://chaster.app/locks/123456789abcdef123456789/settings`

The number you need is the one after `locks`; in this example it would be
`123456789abcdef123456789`.

You can enter this into the "Set Lock Session" field.  If you enter the
right value the status will switch to something like:

```
Lock id: 123456789abcdef123456789
  Title: Self-lock
  State: locked
```

The safe is now locked and you won't be able to open it until the lock
finishes on chaster.app

### Refresh status

Every time you reload the web page or click the "Status" button, the
safe will reconnect to the API and check the lock status.  This isn't
always fast because the ESP8266 isn't a fast CPU.  It can take between
2 and 10 seconds.  This is because we use TLS to prevent "man in the
middle" attacks.  After all, we don't want to be able to unlock the
safe early!

If there are communication issues then these will be displayed.

*IMPORTANT* if you lose internet access or the server goes down or
there's some other problem then you can't refresh the status!
ALWAYS ensure you have a backup key...

### Lock completion

Once a lock has reached "unlocked" state then the safe will delete
the lockID, which will then let you open it.

```
Lock id: 123456789abcdef123456789
  Title: Self-lock
  State: locked

This lock is now available to unlock, and has been removed from the safe
```

## Deploying the software

The code repo contains a prebuilt `bin` and `img` files, built with 4M1M.

On unix this can be written, from the command line with an instruction
similar to
```
python3 ~/.arduino15/packages/esp8266/hardware/esp8266/*/tools/esptool/esptool.py --port=/dev/ttyUSB0 write_flash 0x0 esp8266-chaster-safe.ino.bin 0x300000 data.img
```

Windows also has an equivalent `esptool.exe` command.

If rebuilding from the IDE then you may need the [LittleFS uploader](https://github.com/earlephilhower/arduino-littlefs-upload), especially for IDEv2.

Ensure you have set the Crystal speed to 160 rather than the default, just
to eek out that little extra performance (SSL is slow on these devices!).
I also recommend a 4M1M model.


## Programming the HW-622

I'm putting this here because that's what I use in the v3 hardware build.

This board comes in a couple of versions; the biggest difference is
whether headers at the top left are present. I recommend getting them
pre-installed because these boards don't have USB connectivity; you
program them using a 3.3V serial adapter connected to them.

Near the power supply input there are 3 pins

```
|   |   | G .
|   |   | R .  .  B
| + | - | T .  .  B
+---+---+
```

The G pin is Ground
The R pin is Rx
The T pin is Tx

You need a 3.3V USB-serial adapter.   Remember that Tx on your adaper may
need to be connected to Rx on the HW622 and vice versa.

Now to get the machine into program mode, you need to join pins and then
power on the board.  This _should_ be enough to get let `esptool` send
flash updates.

After programming has completed, remove the B link and then power cycle.

Note that you can also short the ESP reset pin to ground instead of
power cycling

```
                     +-------------+
  first pin here --> |             |
                     |             |
                     |             |
                     |             |
                     |             |
                     |             | <-- first pin here
                     +-------------+

                  |   |   |   .
                  |   |   |   .  .
                  | + | - |   .  .
                  +---+---+
```

