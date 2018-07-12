open Jest;

open Expect;

let buildSale = (name, taxRate) : Sale.t => {
  sku: name,
  productName: name,
  salePrice: 1234,
  taxRate,
  quantity: 1,
  suggestedPrice: 0,
  discounts: [],
};

describe("The group by functions", () =>
  describe("when grouping items in a list by some key", () => {
    describe("where items are simple ints", () => {
      let groups = [1, 2, 3, 1, 2, 3] |> Group.by(x => x |> string_of_int);
      test("it should group the ints", () =>
        expect(groups)
        |> toEqual(
             Group.[
               {key: "1", value: [1, 1]},
               {key: "2", value: [2, 2]},
               {key: "3", value: [3, 3]},
             ],
           )
      );
    });
    describe("when getting a group of sales by taxRate", () => {
      let groups =
        [
          buildSale("bread", 15),
          buildSale("bread", 10),
          buildSale("bread", 15),
          buildSale("bread", 10),
          buildSale("cheese", 15),
          buildSale("cheese", 10),
        ]
        |> Group.by((x: Sale.t) => x.taxRate |> string_of_int);
      test("it should group them correctly", () =>
        expect(groups)
        |> toEqual(
             Group.[
               {
                 key: "10",
                 value: [
                   buildSale("bread", 10),
                   buildSale("bread", 10),
                   buildSale("cheese", 10),
                 ],
               },
               {
                 key: "15",
                 value: [
                   buildSale("bread", 15),
                   buildSale("bread", 15),
                   buildSale("cheese", 15),
                 ],
               },
             ],
           )
      );
    });
    describe("where items are sales", () => {
      let groups =
        [
          buildSale("bread", 15),
          buildSale("bread", 15),
          buildSale("bread", 15),
          buildSale("bread", 15),
          buildSale("cheese", 15),
          buildSale("cheese", 15),
        ]
        |> Group.by((x: Sale.t) => x.productName);
      test("it should group sales by product name", () =>
        expect(groups)
        |> toEqual(
             Group.[
               {
                 key: "bread",
                 value: [
                   buildSale("bread", 15),
                   buildSale("bread", 15),
                   buildSale("bread", 15),
                   buildSale("bread", 15),
                 ],
               },
               {
                 key: "cheese",
                 value: [buildSale("cheese", 15), buildSale("cheese", 15)],
               },
             ],
           )
      );
    });
  })
);