open Jest;

open Expect;

describe("OrderItem functions", () =>
  describe("when assigning notes to an order", () => {
    describe("when the order has no notes", () =>
      test("it assigns the notes correctly", () => {
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
        let orderItemNotes: list(OrderItemNote.t) = [
          {id: "1", value: "Test note 1"},
          {id: "2", value: "Test note 2"},
          {id: "3", value: "Test note 3"},
        ];
        let updatedOrderItem =
          OrderItem.assignNotes(orderItem, orderItemNotes);
        expect(updatedOrderItem.notes |> List.length)
        |> toEqual(orderItemNotes |> List.length);
      })
    );
    describe("when the order already has notes", () =>
      test("it assigns the notes correctly", () => {
        let orderItem: OrderItem.t = {
          id: "",
          quantity: 1,
          notes: [{id: "1", value: "Test note 1"}],
          sku: "PizzaPep",
          name: "Pizza Peperoni",
          suggestedPrice: 20000,
          taxCalculation: TotalFirst(15),
          addedOn: 1.1,
          salePrice: 20000,
        };
        let orderItemNotes: list(OrderItemNote.t) = [
          {id: "2", value: "Test note 1"},
          {id: "3", value: "Test note 2"},
          {id: "4", value: "Test note 3"},
        ];
        let updatedOrderItem =
          OrderItem.assignNotes(orderItem, orderItemNotes);
        expect(updatedOrderItem.notes |> List.length)
        |> toEqual(
             (orderItem.notes |> List.length) + (orderItemNotes |> List.length),
           );
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
          expect(updatedOrderItem.notes |> List.length)
          |> toEqual(orderItem.notes |> List.length);
        })
      );
      describe("when the value is an empty string", () =>
        test("it should not assign the note", () => {
          let orderItemNotes: list(OrderItemNote.t) = [
            {id: "1", value: ""},
          ];
          let updatedOrderItem =
            OrderItem.assignNotes(orderItem, orderItemNotes);
          expect(updatedOrderItem.notes |> List.length)
          |> toEqual(orderItem.notes |> List.length);
        })
      );
    });
  })
);