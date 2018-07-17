type t = {
  id: string,
  value: string,
};

let mapOrderItemNoteFromJs = noteJs : t => {
  id: noteJs##id,
  value: noteJs##value,
};

let orderItemNoteToJs = (orderItemNote: t) => {
  "id": orderItemNote.id,
  "value": orderItemNote.value,
};