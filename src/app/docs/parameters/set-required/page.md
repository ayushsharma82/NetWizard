---
title: setRequired
nextjs:
  metadata:
    title: setRequired
    description: Learn more about on how to set parameters as required or optional in NetWizard, this is helpful when you only want certain parameters from users which are absolutely requrired while having certain optional parameters.
---

{% callout title="Note" %} This feature is available in NetWizard >= v1.2.0 {% /callout %}

All parameters by default are "required" in NetWizard which ultimately means it's necessary for user to enter all input parameters before proceeding to finish the setup.

While this approach is fine if all the parameters you are adding to NetWizard portal should be entered by user; but in certain scenarios where you have to keep some input parameters as optional then you may use the following API:

## API Reference

### Constructor Method

The 6th param in NetWizardParameter constructor is a boolean which can be set to `true` or `false` to toggle requiredness of the parameter. (`true` = required and `false` = optional)

```cpp
// Input parameter as optional example
NetWizardParameter nw_input(&NW, NW_INPUT, "Name", "Value", "Placeholder", false);
```

### Function Method

Additionally, you can also toggle the requiredness of the parameter from anywhere in your code (apart from global scope) using the `setRequired` function.(`true` = required and `false` = optional)

```cpp
nw_input.setRequired(false);
```
