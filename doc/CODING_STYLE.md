# Racon Style Guide

- This style guide was derived from the GNU Coding Standards:

  + It is recommended that you read this document (GCS) before
  contributing.

# C Version

- Follow the C99 Standard (*ISO/IEC 9899:TC3*);

- Do not use any non-standard extensions.

# Comment Style

- Use `/* <...>  */` for one-lined comments:

  + Always terminate with double spaces before the end of the comment.

- Use

  ```
  /* <...>
   * <...>
   */
  ```

  for multi-lined comments.

## Prepocessor Comments

- Always end a `#ifdef` and `#ifndef` with a comment: `/* <MACRO>  */` and
`/* !<MACRO>  */`, respectively:

  + In case of `#else` directives, put the normal comment in the `#else`
  and the inverse in the end of the conditional directive, e.g.:

    ```
    #ifdef <MACRO>
    <...>
    #else /* <MACRO>  */
    <...>
    #endif /* !<MACRO>  */
    ```

## Header Guards

- All header files shall have a guard to prevent multiple inclusions;

- The guard macro must have the form `<FILE>_H`;

- Structure the header guard in the following manner:

  ```
  #ifndef <FILE>_H
  # define <FILE>_H
  <...>
  #endif /* !<FILE>_H  */
  ```

# Order

## Source File Order

1. Inclusion of its correspondent header file;

2. Private macros;

3. Private type definitions;

4. Public constants definition;

5. Private constants definition;

6. Private variables definition;

7. Private functions prototypes:

   - Put it into a `#ifndef DEBUG` block, for testing purposes; declare
   it with the `static` scope.

8. Public functions definition;

9. Private functions definition:

   - Use the `SCOPE` macro before the type name and qualifier for the
   determination of the scope.

## Header File Order

1. Start of the header guard;

2. Standard library header files;

3. Third-party header files;

4. Racon header files;

5. Public macros;

6. Public type definitions;

7. Public constants declaration;

8. Public inline functions definition;

9. Public functions prototypes;

10. Private functions prototypes for testing purposes;

11. End of the header guard.

### Inclusion Order

- Include files in alphabetical order:

  + Exception: include `gmp.h` before `mpfr.h`.
