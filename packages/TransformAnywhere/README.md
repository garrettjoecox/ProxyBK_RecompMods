# TransformAnywhere
Transform into Mumbo's forms anywhere, with optional restrictions

## Allowed Transformations
- "All"
    - D-pad Up: Wishwashy
    - D-pad Down: Croc (or Walrus)
    - D-pad Left: Bee
    - D-pad Right: Termite (or Pumpkin)
- "Current World"
    - D-pad Up: Transform to the form from the current world, and back to Banjo.
- "Banjo"
    - D-pad Up: Transform instantly back to Banjo only. Requires going back to Mumbo to transform.
- "None"
    - The mod is effectively disabled

## Token Payment
- Yes: Requires having paid Mumbo for the transformation in the current game file
- No: Does not require having paid Mumbo

## Button Mode
- "D-pad": Only requires that the D-pad button alone be pressed for the transformation
- "L + D-pad": Requires L to be held while pressing D-pad directions for the transformation

## TODO / Known Issues
- When transforming from bee to banjo, banjo's scale is smaller till you stop moving

## Changelog
- 0.0.1
    - Initial release
- 0.0.2
    - Prevent transformation when in map transition (was causing soft locks)
- 0.0.3
    - Add configuration options for transformation restrictions and token payment requirements
    - Fix issue where player death while transformed could cause soft lock
    - Prevent Mumbo from tranforming player at boundaries when in "All" mode
