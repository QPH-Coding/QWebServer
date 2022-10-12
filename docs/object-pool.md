# Object Pool

## Overview

The Object Pool has these features:

- Thread safe

- Use template

- Customize object init and destruct function

## Design

The Object Pool use a `std::vector` to store its objects, and use a `std::queue` to store the free objects' index.

While calling the function `get_one()`, it will return the object's reference, and pop this object index from the `free_queue`.

Sometimes, we want to init the object and do something before the object destruct. Considering this request, I add some members in this Object Pool and call the init and destruct function at the correct moment.

## Usage

If you use `get_one()`, you should use `give_back_one()` after you finish using this object, just like the relationship between `new` and `delete`. So I recommend using the RAII to use the Object Pool.