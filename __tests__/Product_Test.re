open Jest;

open Expect;

let buildProduct =
    (
      name: string,
      tags: list(string),
      startDate: option(Date.t),
      endDate: option(Date.t),
    )
    : Product.t => {
  id: "123",
  sku: "123",
  name,
  department: "dept",
  unit: "pieces",
  location: "",
  weight: 0,
  startDate,
  endDate,
  tags,
  products: [],
  suggestedPrice: 1000,
  taxCalculation: Exempt,
};

describe("product related utilities", () =>
  describe("js obj mapping", () =>
    test("it should be able to map an existing product from js", () => {
      let js = {
        "_id": "982f1879-c98c-441a-8149-ba6282e8db58",
        "_rev": "1-cb789488740c442cba15653323c005bb",
        "sku": "fasdf",
        "name": "fasdf",
        "department": "dept",
        "location": "location",
        "unit": "pieces",
        "startDate": Js.Nullable.undefined,
        "endDate": Js.Nullable.undefined,
        "onHand": 0,
        "weight": 0,
        "suggestedPrice": 3543534,
        "tags": ["fsdafsda"],
        "products": Js.Nullable.undefined,
        "taxCalculation": "exempt|",
      };
      let product: Product.t = js |> Product.mapFromJs;
      expect(product.id) |> toEqual(js##_id);
    })
  )
);

describe("product data functions", () => {
  describe("filtering products by tag", () =>
    test("it should return only relevant products", () => {
      let result =
        Product.filterProducts(
          "a",
          [
            buildProduct("plate", ["a"], None, None),
            buildProduct("platter", ["b"], None, None),
            buildProduct("bowl", ["a"], None, None),
          ],
        );
      expect(result)
      |> toEqual([
           buildProduct("plate", ["a"], None, None),
           buildProduct("bowl", ["a"], None, None),
         ]);
    })
  );
  describe("getting only unique tags", _ =>
    test("it should return a list of unique tags", _ => {
      let result =
        Product.getTags([
          buildProduct("coffee", ["a"], None, None),
          buildProduct("latte", ["b"], None, None),
          buildProduct("macchiato", ["a"], None, None),
          buildProduct("white", ["c", "d", "a"], None, None),
          buildProduct("black", ["b"], None, None),
          buildProduct("au lait", ["a"], None, None),
        ]);
      expect(result |> List.length) |> toBe(4) |> ignore;
      expect(result) |> toEqual(["a", "b", "c", "d"]);
    })
  );
});