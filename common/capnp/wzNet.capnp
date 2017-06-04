@0xc1fb4f9ae0b77ec1;

interface WZNet {
  evaluate @0 (expression :Expression) -> (value :Value);
  struct Expression {
    union {
      literal @0 :Float64;
      previousResult @1 :Value;
      parameter @2 :UInt32;
      call :group {
        function @3 :Function;
        params @4 :List(Expression);
      }
    }
  }

  interface Value {
    read @0 () -> (value :Float64);
  }

  defFunction @1 (paramCount :Int32, body :Expression) -> (func :Function);

  interface Function {
    call @0 (params :List(Float64)) -> (value :Float64);
  }

  getOperator @2 (op :Operator) -> (func :Function);

  enum Operator {
    add @0;
    subtract @1;
    multiply @2;
    divide @3;
  }
}
