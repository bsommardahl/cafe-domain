open Jest;

open Expect;

describe("OrderItem functions", () =>
  describe("when assigning notes to an order", () => {
    describe("when there are notes with valid values", () =>
      test("it assigns the notes correctly", () => {
        let orderItem: OrderItem.t = {
          id: "",
          quantity: 1,
          notes: [
            {id: "1", value: "Test note 1"},
            {id: "2", value: "Test note 2"},
            {id: "3", value: "Test note 3"},
          ],
          sku: "PizzaPep",
          name: "Pizza Peperoni",
          suggestedPrice: 20000,
          taxCalculation: TotalFirst(15),
          addedOn: 1.1,
          salePrice: 20000,
        };
        let orderItemNotes: list(OrderItemNote.t) = [
          {id: "1", value: "Test note 1"},
          {id: "2", value: "Test note 2"},
          {id: "5", value: "Test note 5"},
          {id: "6", value: "Test note 6"},
        ];
        let updatedOrderItem =
          OrderItem.assignNotes(orderItem, orderItemNotes);
        expect(updatedOrderItem.notes) |> toEqual(orderItemNotes);
      })
    );
    describe("when there is a note with empty values", () => {
      let orderItem: OrderItem.t = {
        id: "",
        quantity: 1,
        notes: [],
        sku: "PizzaPep",
        name: "Pizza Peperoni",
        suggestedPrice: 20000,
        taxCalculation: TotalFirst(15),
        addedOn: 1.1,
        salePrice: 20000,
      };
      describe("when the id is an empty string", () =>
        test("it should not assign the note", () => {
          let orderItemNotes: list(OrderItemNote.t) = [
            {id: "", value: "Test note 1"},
          ];
          let updatedOrderItem =
            OrderItem.assignNotes(orderItem, orderItemNotes);
          expect(updatedOrderItem.notes) |> toEqual([]);
        })
      );
      describe("when the value is an empty string", () =>
        test("it should not assign the note", () => {
          let orderItemNotes: list(OrderItemNote.t) = [
            {id: "1", value: ""},
          ];
          let updatedOrderItem =
            OrderItem.assignNotes(orderItem, orderItemNotes);
          expect(updatedOrderItem.notes) |> toEqual([]);
        })
      );
    });
  })
);