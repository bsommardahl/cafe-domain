type t = {
  id: int,
  value: string,
};

let mapOrderItemNoteFromJs = itemJs : t => {
  id: itemJs##id,
  value:
    switch (Js.Null_undefined.toOption(itemJs##value)) {
    | Some(quantity) => quantity
    | None => ""
    },
};

let orderItemNoteToJs = (orderItemNote: t) => {
  "id": orderItemNote.id,
  "value": orderItemNote.value,
};