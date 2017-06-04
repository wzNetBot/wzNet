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

  enum DroidAction {
    none @0;
    move @1;
    build @2;
    uNUSED3 @3;
    demolish @4;
    repair @5;
    attack @6;
    observe @7;
    firesupport @8;
    sulk @9;
    uNUSED10 @10;
    transportOut @11;
    transportWaitToFlyIn @12;
    transportIn @13;
    droidRepair @14;
    restore @15;
    uNUSED16 @16;
    moveFire @17;
    moveToBuild @18;
    moveToDemolish @19;
    moveToRepair @20;
    buildWander @21;
    uNUSED22 @22;
    moveToAttack @23;
    rotateToAttack @24;
    moveToObserve @25;
    waitForRepair @26;
    moveToRepairPoint @27;
    waitDuringRepair @28;
    moveToDroidRepair @29;
    moveToRestore @30;
    uNUSED31 @31;
    moveToRearm @32;
    waitForRearm @33;
    moveToRearmPoint @34;
    waitDuringRearm @35;
    vtolAttack @36;
    clearRearmPad @37;
    returnToPos @38;
    firesupportRetreat @39;
    uNUSED40 @40;
    circle @41;
  }
}
