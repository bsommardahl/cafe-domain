open Jest;

open Expect;

let buildOrderItem =
    (name: string, salePrice: int, taxRate: int)
    : OrderItem.t => {
  sku: name,
  name,
  suggestedPrice: 0,
  addedOn: 0.0,
  salePrice,
  taxCalculation: Tax.SubTotalFirst(taxRate),
};

let buildOrder = items : Order.t => {
  id: "test",
  customerName: "test",
  orderItems: items,
  paid:
    Some({
      on: 0.0,
      by: "test",
      discount: 0,
      subTotal: 0,
      tax: 0,
      total: 0,
      transactionId: "",
    }),
  returned: None,
  createdOn: 0.0,
  discounts: [],
  lastUpdated: None,
  removed: false,
  meta: "",
};

let buildSale = (name, salePrice, taxRate: int) : Sale.t => {
  sku: name,
  productName: name,
  taxRate,
  salePrice,
  suggestedPrice: 0,
  discounts: [],
};

describe("The sale module", () =>
  describe("when extracting a list of sales from an order", () =>
    describe("where it is a normal order", () => {
      let order =
        buildOrder([
          buildOrderItem("bread", 101, 18),
          buildOrderItem("bread", 101, 18),
          buildOrderItem("cheese", 202, 18),
        ]);
      let sales = order |> Sale.listOfSales;
      let bread = buildSale("bread", 101, 18);
      let cheese = buildSale("cheese", 202, 18);
      test("it should give a list of sales", () =>
        expect(sales) |> toEqual([bread, bread, cheese])
      );
    })
  )
);