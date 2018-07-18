type t = {
  id: string,
  value: string,
};

let mapOrderItemNoteFromJs = noteJs : t =>
  switch (Js.Null_undefined.toOption(noteJs)) {
  | Some(noteJs) => {id: noteJs##id, value: noteJs##value}
  | None => {id: "", value: ""}
  };

let orderItemNoteToJs = (orderItemNote: t) => {
  "id": orderItemNote.id,
  "value": orderItemNote.value,
};