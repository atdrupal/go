/admin/go-doc/roles

    Machine name    | Is admin
    --------------------------
    Role 0 (role_0) | x
    Role 1 (role_1) | x

    Permission matrix

      {{ same permission management page, just no form here }}

/admin/go-doc/content-types

  Access permissions

    -------------------------------
     Content Type X (machine_name)  <<< Click to go to /go-doc/content-types/x-machine-name
    -------------------------------
           | Read | Write | Delete
    -------------------------------
    Role 0 | x    | x     | x
    Role 1 | x    | x     | x

    -------------------------------
     Content Type Y (machine_name)
    -------------------------------
           | Read | Write | Delete
    -------------------------------
    Role 0 | x    | x     | x
    Role 1 | x    | x     | x

/admin/go-doc/content-types/x-machine-name

  %description

  Access Permission

           | Read | Write | Delete
    ------------------------------
    Role 0 | x    | x     | x
    Role 1 | x    | x     | x

  Fields list

    Name                                   | Type     | Widget
    ------------------------------------------------------------
    Category (field_category)              | taxonony | term_reference
      Category feature for products        |          |
                                           |          |
      Field Permissions                    |          |
                                           |          |
              | Role 0 | Role 1 | Role 2   |          |
      ----------------------------------   |          |
      Field A | x      | x      | x        |          |
      Field B | x      | x      | x        |          |
      Field C | x      | x      | x        |          |
                                           |          |

  Content type is used on views <<<< click to view view-doc details

    View name                 | Tags
    ----------------------------------------------
    View X (view_x)           | tag_1, tag_2
                              |
      list blog entries…      |
                              |
      Access: …               |
      Entity: …               |
      Fields: …               |
                              |

  Content type is used on contexts <<<< click to view context-doc details

    …

/admin/go-doc/views

  …

/admin/go-doc/contexts

  …

/admin/go-doc/modules

  Package | Module
  --------------------------------------------------------------------
  Ctools  | Page management (page_management 7.x-1.8)
          |
          |   Description…
          |   Depends on: …
          |
