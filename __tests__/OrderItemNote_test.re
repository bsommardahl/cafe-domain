open Jest;

open Expect;

describe("OrderItemNote functions", () => {
  describe("when converting a Reason record to a JavaScript object", () =>
    test("it should convert with the correct property names and values", () => {
      let orderItemNote: OrderItemNote.t = {id: "1", value: "Test note 1"};
      let js = orderItemNote |> OrderItemNote.orderItemNoteToJs;
      expect(js) |> toEqual({"id": "1", "value": "Test note 1"});
    })
  );
  describe("when converting a JavaScript object to a Reason record", () => {
    describe("with undefined JavaScript object", () =>
      test("it should convert with default empty values", () => {
        let js = Js.Nullable.undefined;
        let orderItemNote: OrderItemNote.t =
          js |> OrderItemNote.mapOrderItemNoteFromJs;
        expect(orderItemNote)
        |> toEqual({OrderItemNote.id: "", OrderItemNote.value: ""});
      })
    );
    describe("with null JavaScript object", () =>
      test("it should convert with default empty values", () => {
        let js = Js.Nullable.null;
        let orderItemNote = js |> OrderItemNote.mapOrderItemNoteFromJs;
        expect(orderItemNote)
        |> toEqual({OrderItemNote.id: "", OrderItemNote.value: ""});
      })
    );
    describe("with initialized JavaScript object", () =>
      test("it should convert with the correct values", () => {
        let js =
          Js.Null_undefined.fromOption(
            Some({"id": "1", "value": "Test note 1"}),
          );
        let orderItemNote = js |> OrderItemNote.mapOrderItemNoteFromJs;
        expect(orderItemNote)
        |> toEqual({
             OrderItemNote.id: "1",
             OrderItemNote.value: "Test note 1",
           });
      })
    );
  });
});