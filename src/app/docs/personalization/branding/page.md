---
title: Branding (Pro)
nextjs:
  metadata:
    title: Branding
    description: Learn more about on how to personalize NetWizard Pro with branding.
---

{% callout title="Pro Feature" %}
This is an exclusive feature of NetWizard Pro. Check it out [here](https://netwizard.pro).
{% /callout %}

![Branding](/branding.png)

NetWizard Pro library contains a spot which can be updated to add your own company/product logo. This enables you with complete personalization and maintains your brand value among customers.

We'll go through the process below:


## Setting Logo

### What you'll need
- You'll need a compatible logo image *(jpeg / png / gif etc)* or an SVG file (recommended due to small file size). **Important: Please make sure your image is optimized and tiny in file size before proceeding.**
- Know the MIME file type of your image. You can use [HTTPStrip's mime utility](https://www.htmlstrip.com/mime-file-type-checker).

### Step 1: Procedure to convert logo into byte array
1. Go to [File2Raw Utility](https://file2raw.labrat.one/) ( I created this utility a few years back for the purpose of converting files into byte array for C++ applications ).
2. Select your logo.
3. Select "Gzip Compress" & "Use PROGMEM (Arduino)".
4. Click "Convert".

### Step 2: Setting custom logo in sketch

Now once your custom logo has been prepared, let's set it in your NetWizard Pro library:

1. Open `logo.h` which can be found inside src folder of your library.
2. Set `NETWIZARD_LOGO_MIME` to your image file type. To find your file's mime type, use this utility: [MIME File Type Checker](https://www.htmlstrip.com/mime-file-type-checker)
3. Set `NETWIZARD_LOGO_WIDTH` & `NETWIZARD_LOGO_HEIGHT` according to your desired size which will be displayed on the webpage.
4. Replace the array length of `NETWIZARD_LOGO` with the newly generated array length.
5. Now open `logo.cpp`
6. Replace the data inside `NETWIZARD_LOGO` with newly generated byte array.

### Step 3: Upload firmware again

That's all there is to it! You can now compile & re-upload your firmware to your microcontroller and begin using NetWizard Pro with your own logo.